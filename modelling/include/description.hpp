#pragma once

#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>

namespace Description
{

    class Value
    {
    public:
        std::vector<uint8_t> data;
        int size;
    };

    class Address
    {
        int start, len;
    };

    class Expression
    {
    public:
        Expression(std::string source);
        std::string source;

        std::string getCode()
        {
            std::string ret = "// " + source;
            auto arrow = source.find("-->");
            std::string left = source.substr(0,arrow);
            std::string right = source.substr(arrow+3);

            

            return "";
        }
    };

    class Instruction
    {
    public:
        Instruction(std::string key, YAML::Node config);

        std::string name = "", description = "", code = "";
        std::vector<std::string> instructions_source;
        std::vector<Expression> expressions;

        std::string getCode(std::string classname)
        {
            std::string ret = "void " + classname + "::" + name + "() {";

            for(auto e : expressions)
            ret += e.getCode();

            
            
            return ret + "}";
        };
        std::vector<std::string> getOPCodes();
    };

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

    class CPU
    {
    public:
        CPU(std::string path);
        std::string name, description;
        std::vector<Memory> memory;
        std::vector<Instruction> instructions;
        int total_mem = 0;

        void generate();

        std::string generateAddressInfos();
        std::string generateMemory();
        std::string generateClass();
        std::string generateFunctions();
        std::string generateHeader();
    };

}