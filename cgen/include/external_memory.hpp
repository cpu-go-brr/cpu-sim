#pragma once

#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <regex>
#include "matheval.hpp"

namespace Description
{

    class ExternalMemory
    {
    private:
    public:
        ExternalMemory(std::string key, YAML::Node config);
        std::string name = "";
        std::size_t words = 0, bits = 0;

        std::string getDeclaration();
        std::string getInit();
        std::string getFunction(const std::string& cpu);
    };
}