#include <regex>
#include "instruction.hpp"


std::string Description::Instruction::getFunction(std::string classname)
{
    std::string ret = "";

    for (auto c : getOPCodes())
    {
        ret += "template <>\nvoid " + classname + "::" + name + "<0b" + c + ">()\n{\n";

        ret += getCode(c);

        ret += "}\n\n";

    }
    return ret;
}
std::string Description::Instruction::getCode(std::string c)
{
    std::string ret = "";

        std::string code_no_whitespace = std::regex_replace(code, std::regex("\\s"), "");

        std::string c_nw = std::regex_replace(c, std::regex("\\s"), "");

        // lets get all of our parameters
        std::map<std::string, std::string> params;
        for (std::size_t i = 0; i < code_no_whitespace.length(); i++)
        {
            if (code_no_whitespace[i] == '0' || code_no_whitespace[i] == '1')
                continue;

            // we have a parameter
            std::string name = std::string(1, code_no_whitespace[i]);
            if (!params.contains(name))
                params[name] = "";

            params[name] += std::string(1, c_nw[i]);
        }

        
        for (auto [key, param] : params)
            ret += "[[maybe_unused]] constexpr std::size_t " + key + " = 0b" + param + ";\n";

        for (auto c : conditions)
            ret += c.getCode();

        for (auto e : expressions)
            ret += e.getCode(params);

    
    return ret;
}


std::vector<std::string> getPossibilities(std::string code)
{
    std::vector<std::string> codes;

    for (auto i = 0ul; i < code.length(); i++)
    {
        if (code[i] == '0' || code[i] == '1')
            continue;


        // we have a parameter
        code[i] = '0';
        auto new_codes_0 = getPossibilities(code);
        codes.insert(codes.end(), new_codes_0.begin(), new_codes_0.end());

        code[i] = '1';
        auto new_codes_1 = getPossibilities(code);
        codes.insert(codes.end(), new_codes_1.begin(), new_codes_1.end());
        return codes;
    }

    return {code};
}

std::vector<std::string> Description::Instruction::getOPCodes()
{
    code.erase(std::remove_if(code.begin(), code.end(), ::isspace), code.end());

    return getPossibilities(code);
}

Description::Instruction::Instruction(std::string key, YAML::Node config)
{
    name = key;
    description = config["description"].as<std::string>("");
    code = config["code"].as<std::string>("");

    auto instr = config["instructions"];
    for (auto i = 0ul; i < instr.size(); i++)
    {
        expressions.push_back(Expression(instr[i].as<std::string>(), code));
    }

    auto con = config["conditions"];
    for (auto i = 0ul; i < con.size(); i++)
    {
        conditions.push_back(Condition(con[i].as<std::string>()));
    }
}


