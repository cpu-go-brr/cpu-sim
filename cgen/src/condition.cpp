#include "condition.hpp"
#include <regex>

CPUDescription::Condition::Condition(std::string cond) : condition{std::regex_replace(cond, std::regex("\\s"), "")} // remove whitespace
{
}

std::string CPUDescription::Condition::getCode()
{
    // Surround internal Memory with "get(..)"
    auto line = "bool " + std::regex_replace(condition, std::regex("[A-Z][A-Z\\[0-9\\]]+"), "get($&)") + ";\n";

    // prefix all Parameter with bool"
    auto equals = line.find('=') + 1;
    auto left = line.substr(0, equals);
    auto right = std::regex_replace(line.substr(equals), std::regex("([A-Z])[&|^]"), "(bool)$&");

    return left + right;
}
