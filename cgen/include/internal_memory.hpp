#pragma once

#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <regex>
#include "matheval.hpp"

namespace Description
{

    class InternalMemory
    {
    private:
    public:
        std::vector<uint8_t> getBitmask();
        InternalMemory(std::string key, YAML::Node config, int total_mem, std::vector<int> dimension = std::vector<int>());
        std::string name = "";
        int size = 0;
        uint8_t *address;
        uint8_t bitoffset = 0;
        int byteoffset = 0;
        std::vector<InternalMemory> submemory;
        std::vector<uint8_t> bitmask;

        static std::map<std::string, std::size_t> address_lengths;
        std::string getJSONDescription();
        // std::vector<uint8_t> get();
        // void set(std::vector<uint8_t> val);
    };
}