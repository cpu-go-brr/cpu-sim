#pragma once

#include <string>
#include "matheval.hpp"

namespace CPUDescription
{
    class Expression
    {
    public:
        Expression(std::string source); //intitialize with source like 0 --> ACC

        //return code 
        std::string getCode(std::map<std::string, std::string> params);
    private:
        const std::string source;
    };
}