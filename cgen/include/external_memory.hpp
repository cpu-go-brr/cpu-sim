#pragma once

#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <regex>
#include "matheval.hpp"

namespace CPUDescription
{

    class ExternalMemory
    {
    public:
        ExternalMemory(std::string key, YAML::Node config);

        std::string getInterfaceDeclaration(); //get code declaration for getter and setter Methods
        std::string getInitCode();  //get code to initialize memory with 0 
        std::string getInterfaceCode(const std::string& cpu); // get code for getter and setter Methods

        //getter functions for private variables
        std::string getName();
        std::size_t getBits();
        std::size_t getWords();
        
    private:
        std::string name = "";
        std::size_t words = 0, bits = 0;
    };
}