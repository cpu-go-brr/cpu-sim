#include "external_memory.hpp"
#include <iostream>
#include <assert.h>
#include <regex>
#include <cmath>
#include <cctype>


Description::ExternalMemory::ExternalMemory(std::string key, YAML::Node config)
{
    name = key;
    words = config["words"].as<int>();
    bits = config["bits"].as<int>();
}

std::string Description::ExternalMemory::getDeclaration()
{
    return "/* "+name+" */\n"
    "bitset " + name + "_mem[" + std::to_string(words) + "];\n"
    "bitset& " + name + "(AddressInfo info);\n"
    "bitset& " + name + "(bitset index);\n"
    "void flash_"+name+"(std::vector<bitset> data);\n\n";

}

std::string Description::ExternalMemory::getInit()
{
    return "for(auto i = 0ul; i < " + std::to_string(words) + "; i ++)\n"
    "" + name + "_mem[i] = bitset(0," + std::to_string(bits) + ");\n";
}


std::string Description::ExternalMemory::getFunction(const std::string& cpu)
{
    return "bitset& " + cpu + "::" + name + "(AddressInfo info)\n"
    "{\n"
    "return " + name + "(get(info));\n"
    "}\n\n"
    "bitset& " + cpu + "::" + name + "(bitset index)\n"
    "{\n"
    "return " + name + "_mem[index.val()];\n"
    "}\n"
    "void "+cpu+"::flash_"+name+"(std::vector<bitset> data)\n"
    "{\n"
    "for(auto i = 0ul; i < data.size(); i++)\n"
    "" + name + "_mem[i] = bitset(data[i], "+ std::to_string(bits) + ");\n"
    "}\n\n";
}