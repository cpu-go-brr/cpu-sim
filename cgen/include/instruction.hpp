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

        std::size_t getSizeOfOPCode();
        std::string getName();
        std::string getDescription();
        std::string generateFunction(std::string opcode); //get only function body
        
    private:

        void initInfo(const std::string& name, const YAML::Node& config);
        void initInstructions(YAML::Node& config);
        void initConditions(YAML::Node& config);

        std::string name = "", description = "", code = "";
        std::vector<Expression> expressions;
        std::vector<Condition> conditions;

    };
}