#pragma once

#include <string>
#include <vector>

#include "instruction.hpp"
#include "memory.hpp"

namespace Description
{

    class CPU
    {
    public:
        CPU(std::string path);
        std::string name, description, display;
        std::vector<Memory> memory;
        std::vector<Instruction> instructions;
        Instruction fetch;
        std::size_t min_opcode_length, max_opcode_length;
        int total_mem = 0;

        void generate();

        std::string generateDisplay();
        std::string generateCMakeFile();
        std::string generateMainFile();
        std::string generateAddressInfos();
        std::string generateMemory();
        std::string generateClass();
        std::string generateFunctions();
        std::string generateHeader();
    };

}