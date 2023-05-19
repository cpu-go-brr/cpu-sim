#pragma once

#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <regex>
#include "matheval.hpp"

namespace CPUDescription
{

    class InternalMemory
    {
    public:
        InternalMemory(std::string key, YAML::Node config, int total_mem, std::vector<int> dimension = std::vector<int>());
        
        //get a json description of the memory for web application
        std::string getJSONDescription();


        //getter functions for private variables
        std::size_t getSize() const;
        std::string getAddressInfo() const;
        std::string getUpperName() const;
        std::vector<std::string> getNames() const;

        //the length of specific adresses in bit
        static std::map<std::string, std::size_t> address_lengths;

    private:
        std::string name = "";
        std::size_t size = 0, bitoffset = 0, byteoffset = 0;
        std::vector<InternalMemory> submemory;
    };
}