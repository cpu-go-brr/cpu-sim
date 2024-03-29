#pragma once

#include <string>
#include <vector>
#include <filesystem>

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
        std::string generateCMakeFile();       // generate CMake File for the CPU
        std::string generateAddressInfos();    // generate the AddressInfos of the CPU
        std::string generateMemory();          // generate the internal Memory
        std::string generateRunScript();       // generate Script to automatically build and Run the code
        std::string generateCpp();             // generate the CPU .cpp
        std::string generateHpp();             // generate the CPU .hpp
        std::string generateDisplayJSONInfo();         // generate sourcecode able to display the cpu
        std::string generateSyntaxHighlighter();         // generate sourcecode able to display the cpu
        std::string generateInstructionCodeMap();         // generate sourcecode able to display the cpu
        std::filesystem::path getPath();

    private:
        std::string generateHppInstructions(); // generate the CPU instructions
        std::string generateHppIncludes();     // generate the Hpp Includes
        std::string generateClass();           // generate the CPU Class
        std::string generateDisplay();         // generate sourcecode able to display the cpu
        std::string generateJSONCpp();             // generate the CPU .hpp
        std::string generateMemorySetAndGetCpp();             // generate the CPU .hpp
        std::string generateFetchCpp();             // generate the CPU .hpp
        std::string generateSimulateCpp();      //generate the simulate .cpp
        std::string generateConstructorCpp();   //Generate the constructor
        std::string generateIncludesCpp();      //generate the includes for the .cpp
        std::string generateExternalMemoryCpp();    //generate the external memory
        std::string generateInstructionsCpp();//generate the instructions memory
        std::string generateInstructionJumpTableCpp();  //generate the jump table
        std::map<std::size_t, std::string> generateInstructionMap();    //generate a map of the instruction map --> opcode to function name
        std::size_t getOpCodeMaxLength();           //get the maximum opcode  length of an instruction


        //init the cpu info
        void initInfo(const YAML::Node &config);       
        //init the internal Memory
        void initInternalMemory(const YAML::Node &config);
        //init ine external Memory
        void initExternalMemory(const YAML::Node &config);
        //init the instructions
        void initInstructions(const YAML::Node &config);

        std::string name, description, display;      // name description and display description of the cpu
        std::filesystem::path cpu_path;              // the path of the cpu file
        std::vector<InternalMemory> internal_memory; // registers, pc etc.
        std::vector<ExternalMemory> external_memory; // rom, ram etc.
        std::vector<Instruction> instructions;       // nop, fim etc.
        Instruction fetch;                           // the fetch cycle
        std::size_t total_mem = 0;                   // the amount of bits
    };

}
