#pragma once

#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <regex>
#include "matheval.hpp"

#include "expression.hpp"
#include "condition.hpp"


namespace Description
{
    class Instruction
    {
    public:
        Instruction(std::string key, YAML::Node config);
        Instruction() = default;

        std::string getCode(std::string code);
        std::string getFunction(std::string classname);
        std::vector<std::string> getOPCodes();

        std::string name = "", description = "", code = "";
        std::vector<Expression> expressions;
        std::vector<Condition> conditions;
        unsigned int bits;

    };
}