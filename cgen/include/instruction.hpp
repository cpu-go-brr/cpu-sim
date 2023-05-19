#pragma once

#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include "expression.hpp"
#include "condition.hpp"


namespace CPUDescription
{
    //a CPU instruction
    class Instruction
    {
    public:
        //set name of instruction and config
        Instruction(std::string name, YAML::Node config);
        Instruction() = default;

        std::string getCode(std::string classname); //get whole Function
        std::vector<std::string> getOPCodes(); //get all possible instruction codes (replace all parameter with 0 or 1)


        //getter functions for private Variables
        std::size_t getSizeOfOPCode() const;
        std::size_t getByteSizeOfOPCode() const;
        
        std::string getName() const;  // get Name of the CPU lowercase
        std::string getFullName() const;
        std::string getUpperName() const;            // get Name of the CPU upprcase
        std::string getOPCode() const;            

        std::string getDescription() const;
        std::string generateFunction(std::string opcode); //get only function body
        
    private:

        //init private variables
        void initInfo(const std::string& name, const YAML::Node& config); 
        void initInstructions(YAML::Node& config);
        void initConditions(YAML::Node& config);

        std::string name = "", full_name = "", description = "", code = "", asm_code = "";
        std::vector<Expression> expressions;
        std::vector<Condition> conditions;

    };
}