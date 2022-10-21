#include "description.hpp"
#include "matheval.hpp"
#include <iostream>
#include <assert.h>
#include <regex>
#include <cmath>
#include <cctype>

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
    }

    codes.push_back(code);

    return codes;
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
        expressions.push_back(Expression(instr[0].as<std::string>()));
    }
}

Description::Expression::Expression(std::string source_)
{
    source = source_;
}

