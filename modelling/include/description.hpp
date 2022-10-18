#pragma once

#include <string>
#include <vector>

namespace Description
{
    class Instruction
    {
        std::string name = "", description = "", code = "", instruction = "";
    };

    class Memory
    {
    private:

    public:
        std::vector<uint8_t> getBitmask();
        Memory(std::string key, YAML::Node config, std::vector<int> dimension = std::vector<int>());
        std::string name = "";
        int size = 0;
        uint8_t* address;
        uint8_t offset = 0;
        std::vector<Memory> submemory;
        std::vector<uint8_t> bitmask;

        std::vector<uint8_t> get();
        void set(std::vector<uint8_t> val);
    };

    class CPU
    {
    public:
        CPU(std::string path);
        std::string name, description;
        std::vector<Memory> memory;
    };

}