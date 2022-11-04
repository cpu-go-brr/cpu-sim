#pragma once

#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <regex>
#include "bitset.hpp"
#include "matheval.hpp"

namespace Description
{

    class Memory
    {
    private:
    public:
        std::vector<uint8_t> getBitmask();
        Memory(std::string key, YAML::Node config, int total_mem, std::vector<int> dimension = std::vector<int>());
        std::string name = "";
        int size = 0;
        uint8_t *address;
        uint8_t bitoffset = 0;
        int byteoffset = 0;
        std::vector<Memory> submemory;
        std::vector<uint8_t> bitmask;

        std::vector<uint8_t> get();
        void set(std::vector<uint8_t> val);
    };
}