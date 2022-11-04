#pragma once

#include <string>

namespace Description
{

    class Condition
    {
        public:
        Condition(std::string cond);

        std::string getCode();
        std::string condition;
    };
}