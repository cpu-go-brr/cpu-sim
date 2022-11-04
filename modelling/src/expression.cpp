#include <string>
#include <vector>
#include <regex>
#include "bitset.hpp"
#include "matheval.hpp"

#include "expression.hpp"

std::string Description::Expression::getCode(std::map<std::string, std::string> params)
{
    std::string comment = "/* " + source + "*/\n";

    // now we want to do the text substitution
    std::smatch sm;
    std::string source_nw = std::regex_replace(source, std::regex("\\s"), "");
    source = source_nw;

    auto arrow = source.find("-->");
    std::string left = source.substr(0, arrow);
    std::string right = source.substr(arrow + 3);

    if (arrow == std::string::npos)
        right = "";
    std::string condition = "";
    auto cond = source.find("?");
    if (cond != std::string::npos)
    {
        condition = left.substr(0, cond);
        left = left.substr(cond + 1);
    }

    const std::regex nums("[^A-Z0-9](0b[01]+)[^A-Z0-9]");
    while (std::regex_search(left, sm, nums))
    {
        std::string number = std::to_string(std::strtoull(sm.str().substr(3).c_str(),NULL, 2));
        std::string len = std::to_string(sm.str().size()-4);
        left = sm.prefix().str() + sm.str().substr(0,1)+"bitset(" + number + "," + len + ")" +sm.str().substr(sm.str().size()-1) + sm.suffix().str();
    }    
    while (std::regex_search(right, sm, nums))
    {
        std::string number = std::to_string(std::strtoull(sm.str().substr(3).c_str(),NULL, 2));
        std::string len = std::to_string(sm.str().size()-4);
        right = sm.prefix().str() + sm.str().substr(0,1)+"bitset(" + number + "," + len + ")" +sm.str().substr(sm.str().size()-1) + sm.suffix().str();
    }


    std::vector<std::pair<std::string, double>> vals;
    for (auto [key, val] : params)
    {
        auto res = std::stol(val, nullptr, 2);
        vals.push_back({key, (double)res});
    }

    const std::regex replacements("[A-Z](\\{[^\\{\\}]*\\})");
    while (std::regex_search(left, sm, replacements))
    {
        // std::cout << sm.str() << "\n";
        std::string match = sm.str().substr(2, sm.length() - 3);
        std::string res = std::to_string((std::size_t)eval(match, vals));
        left = sm.prefix().str() + sm.str().substr(0,1) + res + sm.suffix().str();
    }

    while (std::regex_search(right, sm, replacements))
    {
        // std::cout << sm.str() << "\n";
        std::string match = sm.str().substr(2, sm.length() - 3);
        std::string res = std::to_string((std::size_t)eval(match, vals));
        right = sm.prefix().str() + sm.str().substr(0,1)+ res + sm.suffix().str();
    }

    while (std::regex_search(condition, sm, replacements))
    {
        // std::cout << sm.str() << "\n";
        std::string match = sm.str().substr(2, sm.length() - 3);
        std::string res = std::to_string((std::size_t)eval(match, vals));
        condition = sm.prefix().str() + sm.str().substr(0,1)+ res + sm.suffix().str();
    }

    const std::regex vars("([A-Z\\{\\[\\]\\}]+[0-9]+|[A-Z\\{\\[\\]\\}]{2,}[0-9]*)");

    left = std::regex_replace(left, vars, "get($&)");
    condition = std::regex_replace(condition, vars, "get($&)");

    std::string ret = "";
    if (right != "")
        ret = "set(" + right + ",(" + left + "));\n";
    else
        ret = "return " + left + ";\n";

    if (condition != "")
        ret = "if(" + condition + ")\n{\n" + ret + "}\n";

    return comment + ret;
}