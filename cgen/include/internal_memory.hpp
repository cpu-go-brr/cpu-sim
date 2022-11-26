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
        std::vector<uint8_t> getBitmask();
        std::string getJSONDescription();

        std::size_t getSize() const;
        std::string getAddressInfo() const;
        static std::map<std::string, std::size_t> address_lengths;

    private:
        std::string name = "";
        std::size_t size = 0;
        uint8_t *address;
        uint8_t bitoffset = 0;
        int byteoffset = 0;
        std::vector<InternalMemory> submemory;
        std::vector<uint8_t> bitmask;
    };
}