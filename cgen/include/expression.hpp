#pragma once

#include <string>
#include <map>
#include "matheval.hpp"

namespace CPUDescription
{
    class Expression
    {
    public:
        Expression(std::string source); //intitialize with source like 0 --> ACC

        //return code 
        std::string getCode(std::map<std::string, std::string> params);

        //helper functions for converting f.e. ACC to cpu.get(ACC)
        static void wrapAddressInGetFunction(std::string &string);
        static void wrapAddressInsideParenthesisInGetFunction(std::string &string);

    private:
        const std::string source;
    };
}