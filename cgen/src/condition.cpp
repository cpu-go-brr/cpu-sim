#include "condition.hpp"
#include <regex>
#include <iostream>

CPUDescription::Condition::Condition(std::string cond)
{
    condition = cond;
}


std::string CPUDescription::Condition::getCode()
{
    condition = std::regex_replace(condition, std::regex("\\s"), "");
    auto line = "bool " + std::regex_replace(condition, std::regex("[A-Z][A-Z\\[0-9\\]]+"), "get($&)") + ";\n";

    auto equals = line.find('=')+1;
    auto left = line.substr(0,equals);
    auto right = std::regex_replace(line.substr(equals), std::regex("([A-Z])[&|^]"), "(bool)$&");

    return left+right;
}
