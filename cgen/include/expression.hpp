#pragma once

#include <string>
#include <vector>
#include <regex>
#include "matheval.hpp"

namespace Description
{
    class Expression
    {
    public:
        Expression(std::string source, std::string code);

        std::string getCode(std::map<std::string, std::string> params);
        std::string source, code;
    };
}