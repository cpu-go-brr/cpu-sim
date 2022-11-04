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