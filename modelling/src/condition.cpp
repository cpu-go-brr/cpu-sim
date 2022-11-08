#include "condition.hpp"
#include <regex>

Description::Condition::Condition(std::string cond)
{
    condition = cond;
}


std::string Description::Condition::getCode()
{
    return "bool " + std::regex_replace(condition, std::regex("[A-Z][A-Z\\[0-9\\]]+"), "get($&)") + ";\n";
}
