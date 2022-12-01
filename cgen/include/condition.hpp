#pragma once

#include <string>

namespace CPUDescription
{
    // A conditional in the CPU Description file
    class Condition
    {
    public:
        Condition(std::string cond); // Initialize the condition with the src

        // get generated Code of the condition
        std::string getCode();

    private:
        const std::string condition;
    };
}