#include <string>
#include <vector>
#include <regex>
#include "matheval.hpp"
#include <iostream>
#include "expression.hpp"

std::tuple<std::string, std::string> split(const std::string &string, const std::string &seperator, bool keepright = false)
{
    //split function by given seperator
    auto p = string.find(seperator);
    if (p == std::string::npos)
        return {keepright ? "" : string, keepright ? string : ""};

    return {string.substr(0, p), string.substr(p + seperator.size())};
}

void substituteBinaryNumbers(std::string &string)
{
    //substitutes binary numbers with their bitset counterpart
    const std::regex nums("[^A-Z0-9](0b[01]+)[^A-Z0-9]");
    std::smatch sm;
    while (std::regex_search(string, sm, nums))
    {
        std::string number = std::to_string(std::strtoull(sm.str().substr(3).c_str(), NULL, 2));
        std::string len = std::to_string(sm.str().size() - 4);
        string = sm.prefix().str() + sm.str().substr(0, 1) + "bitset(" + number + "," + len + ")" + sm.str().substr(sm.str().size() - 1) + sm.suffix().str();
    }
}

std::vector<std::pair<std::string, double>> convertParameter(const std::map<std::string, std::string> &params)
{
    // convert parameter from (string, string) to (string, double)
    std::vector<std::pair<std::string, double>> vals;
    for (auto [key, val] : params)
    {
        auto res = std::stol(val, nullptr, 2);
        vals.push_back({key, (double)res});
    }
    return vals;
}

void evaluateCurlyBrackets(std::string &string, std::vector<std::pair<std::string, double>> vals)
{
    //calculate the mathematical equations inside the curly brackets
    const std::regex replacements("[A-Z](\\{[^\\{\\}]*\\})");
    std::smatch sm;

    while (std::regex_search(string, sm, replacements))
    {
        std::string match = sm.str().substr(2, sm.length() - 3);
        std::string res = std::to_string((std::size_t)MathExpression::eval(match, vals));
        string = sm.prefix().str() + sm.str().substr(0, 1) + res + sm.suffix().str();
    }
}

void CPUDescription::Expression::wrapAddressInGetFunction(std::string &string)
{
    //wrap Addresses in a get function
    const std::regex vars("([A-Z_\\{\\[\\]\\}]+[0-9]+|[A-Z_\\{\\[\\]\\}]{2,}[0-9]*)");
    string = std::regex_replace(string, vars, "get($&)");
}

void CPUDescription::Expression::wrapAddressInsideParenthesisInGetFunction(std::string &string)
{
    //wrap Addresses in a get function, even if they are in a function call

    const std::regex function_parameters("[A-Z_]{2,}|[A-Z_]+[0-9]+");
    const std::regex is_function("[a-z_]+\\(.*");

    //return if string is not a function
    if(!std::regex_match(string, is_function)) 
        return;

    std::smatch m;


    //loop over input string
    std::string input = string;
    string = "";
    while (std::regex_search (input,m,function_parameters)) 
    {       
        std::string parameters = m[0];
        string += m.prefix().str() + "get(" + parameters + ")";
        input = m.suffix().str();
    }
    string += input;
}

std::size_t getAddressCount(const std::string &string)
{
    //look how many addresses are in the first level of a parameter call
    std::size_t commas = 0;
    int level = 0;
    for (std::size_t p = 0; p < string.size(); p++)
    {
        if (string[p] == '(')
            level++;
        if (string[p] == ')')
            level--;
        if (level == 0 && string[p] == ',')
            commas++;
    }

    return commas;
}

std::string assembleExpressionParts(std::string condition, std::string left, std::string right)
{

    std::string ret = "";
    if (right != "")
    {
        //if multiple arguments allocate address vector on stack
        std::size_t commas = getAddressCount(right);
        std::string prev = "", suff = "";
        if (commas > 0)
        {
            prev = "{\nconst AddressInfo __addr_infos[" + std::to_string(commas + 1) + "] = {" + right + "};\n";
            right = std::to_string(commas + 1) + ",__addr_infos";
            suff = "}\n";
        }

        ret = prev + "set((" + left + "), " + right + ");\n" + suff;
    }
    else
        ret = "return " + left + ";\n";

    // apply condition
    if (condition != "")
        ret = "if(" + condition + ")\n{\n" + ret + "}\n";

    return ret;
}

std::string CPUDescription::Expression::getCode(std::map<std::string, std::string> params)
{
    //add comment to top
    std::string comment = "/* " + source + "*/\n";

    //some initializations
    std::string condition = "", left = "", right = "", source_nw = std::regex_replace(source, std::regex("\\s"), "");

    //evaluate all formulas in curly brackets
    evaluateCurlyBrackets(source_nw, convertParameter(params));

    //split the argzment in two halves
    std::tie(left, right) = split(source_nw, "-->");

    //wrap memory adresses
    wrapAddressInGetFunction(left);

    //split the condition if it exists
    std::tie(condition, left) = split(left, "?", true);

    //substituteBinaryNumbers
    substituteBinaryNumbers(left);
    substituteBinaryNumbers(right);

    //wrap the adresses in the right portion of the function
    wrapAddressInsideParenthesisInGetFunction(right);

    //add comment in front
    return comment + assembleExpressionParts(condition, left, right);
}

CPUDescription::Expression::Expression(std::string source_) : source{source_} {}
