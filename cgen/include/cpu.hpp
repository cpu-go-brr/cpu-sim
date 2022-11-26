#pragma once

#include <string>
#include <vector>

#include "instruction.hpp"
#include "internal_memory.hpp"
#include "external_memory.hpp"

namespace CPUDescription
{
    // Class to contain a Description of a CPU
    class CPU
    {
    public:
        CPU(std::string yaml_file); // path to the cpu description file file

        std::string getName();                 // get Name of the CPU
        std::string getLowerName();            // get Name of the CPU lowercase
        std::string getDescription();          // get the description of the file
        std::string generateDisplay();         // generate sourcecode able to display the cpu
        std::string generateCMakeFile();       // generate CMake File for the CPU
        std::string generateAddressInfos();    // generate the AddressInfos of the CPU
        std::string generateMemory();          // generate the internal Memory
        std::string generateClass();           // generate the CPU Class
        std::string generateRunScript();       // generate Script to automatically build and Run the code
        std::string generateHppInstructions(); // generate the CPU instructions
        std::string generateHppIncludes();     // generate the Hpp Includes
        std::string generateCpp();             // generate the CPU .cpp
        std::string generateHpp();             // generate the CPU .hpp

    private:
        void extractInfo(const YAML::Node &config);
        void initInternalMemory(const YAML::Node &config);
        void initExternalMemory(const YAML::Node &config);
        void initInstructions(const YAML::Node &config);

        std::string name, description, display;      // name description and display description of the cpu
        std::vector<InternalMemory> internal_memory; // registers, pc etc.
        std::vector<ExternalMemory> external_memory; // rom, ram etc.
        std::vector<Instruction> instructions;       // nop, fim etc.
        Instruction fetch;                           // the fetch cycle
        std::size_t total_mem = 0;                   // the amount of bits
    };

}
