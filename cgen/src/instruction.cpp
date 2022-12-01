#include <regex>
#include "instruction.hpp"

std::string CPUDescription::Instruction::getCode(std::string classname)
{
    std::string ret = "";

    for (auto c : getOPCodes())
    {
        ret += "template <>\nvoid " + classname + "::" + name + "<0b" + c + ">()\n{\n" +
               generateFunction(c) +
               "}\n\n";
    }
    return ret;
}

std::size_t CPUDescription::Instruction::getSizeOfOPCode()
{
    return code.size();
}
std::string CPUDescription::Instruction::getName()
{
    return name;
}
std::string CPUDescription::Instruction::getDescription()
{
    return description;
}

std::map<std::string, std::string> getParameter(const std::string &code, const std::string &opcode)
{
    // code   is something like 00101RRR
    // opcode is something like 00101010
    // we want to extract R --> 010 out of it

    std::map<std::string, std::string> params;
    for (std::size_t i = 0; i < code.length(); i++)
    {
        if (code[i] == '0' || code[i] == '1')
            continue; // current position is not a parameter

        // we have a parameter
        std::string name = std::string(1, code[i]); // name of our parameter
        params[name] += std::string(1, opcode[i]);  // add our value
    }
    return params;
}

std::string CPUDescription::Instruction::generateFunction(std::string opcode)
{
    std::string ret = "";

    // lets get all of our parameters
    auto params = getParameter(code, opcode);
    for (auto [key, param] : params)
        ret += "[[maybe_unused]] bitset " + key + "{0b" + param + ", " + std::to_string(param.size()) + "};\n";

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

std::vector<std::string> CPUDescription::Instruction::getOPCodes()
{
    return getPossibilities(code);
}

void CPUDescription::Instruction::initInfo(const std::string &name_, const YAML::Node &config)
{
    name = name_;
    description = config["description"].as<std::string>("");
    code = std::regex_replace(config["code"].as<std::string>(""), std::regex("\\s"), "");
}

void CPUDescription::Instruction::initInstructions(YAML::Node &config)
{
    auto instr = config["instructions"];
    for (auto i = 0ul; i < instr.size(); i++)
    {
        expressions.push_back(Expression(instr[i].as<std::string>()));
    }
}

void CPUDescription::Instruction::initConditions(YAML::Node &config)
{
    auto con = config["conditions"];
    for (auto i = 0ul; i < con.size(); i++)
    {
        conditions.push_back(Condition(con[i].as<std::string>()));
    }
}

CPUDescription::Instruction::Instruction(std::string key, YAML::Node config)
{
    initInfo(key, config);
    initInstructions(config);
    initConditions(config);
}
