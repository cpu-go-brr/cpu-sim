#pragma once

#include <string>
#include <vector>

#include "instruction.hpp"
#include "internal_memory.hpp"
#include "external_memory.hpp"

namespace Description
{

    class CPU
    {
    public:
        CPU(std::string path);
        std::string name, description, display;
        std::vector<InternalMemory> internal_memory;
        std::vector<ExternalMemory> external_memory;
        std::vector<Instruction> instructions;
        Instruction fetch;
        std::size_t min_opcode_length, max_opcode_length;
        int total_mem = 0;

        void generate(std::string path);

        std::string lowername();
        std::string generateDisplay();
        std::string generateCMakeFile();
        std::string generateAddressInfos();
        std::string generateMemory();
        std::string generateClass();
        std::string generateRunScript();
        std::string generateFunctions();
        std::string generateHeader();
        std::string generateCpp();
        std::string generateHpp();
        
    };

}