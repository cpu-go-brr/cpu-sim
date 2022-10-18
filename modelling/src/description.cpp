#include "yaml-cpp/yaml.h"
#include "../include/description.hpp"
#include "../include/matheval.hpp"
#include <iostream>
#include <assert.h>
#include <regex>
#include <cmath>

Description::CPU::CPU(std::string path)
{

    auto file = YAML::LoadFile(path);

    name = file["name"].as<std::string>();
    description = file["description"].as<std::string>();

    auto mem = file["memory"];

    int total_mem = 0;
    for (YAML::const_iterator it = mem.begin(); it != mem.end(); ++it)
    {
        Memory m(it->first.as<std::string>(), it->second);
        total_mem +=m.size;
        memory.push_back(m);
    }

    for(const auto& m : memory)
    {
        std::cout << m.name << ": " << m.size << "\n";
        for(const auto& m2 : m.submemory)
        {
                    std::cout <<  " "  << m2.name << ": " << m2.size << "\n";

                    for(const auto& m3 : m2.submemory)
        std::cout << "   " << m3.name << ": " << m3.size << "\n";


        }

    }



}

int parseNumber(std::string number)
{
    if (number[0] == '$') // Hex
        return std::strtoul(number.substr(1).c_str(), nullptr, 16);
    if (number[0] == '%') // Binary
        return std::strtoul(number.substr(1).c_str(), nullptr, 2);

    return std::stoi(number);
}

std::pair<std::string, int> getDimension(std::string name)
{
    const std::regex r("(\\w+)\\[([$%]?\\d+)\\]");
    std::smatch matches;

    if (!std::regex_match(name, matches, r))
        return {name, 1};

    return {matches[1], parseNumber(matches[2])};
}

std::string getName(std::string name, std::vector<int> dimensions)
{
    int i = 0;

    // replace all the $0 $1 ...
    for (const auto &dims : dimensions)
    {
        std::regex r("\\$" + std::to_string(i));
        name = std::regex_replace(name, r, std::to_string(dims));
        i++;
    }

    // calculate all numbers in string
    const std::regex r(".*\\{(.+)\\}");
    std::smatch matches;

    while (std::regex_match(name, matches, r))
    {
        std::string match = matches[1].str(); // string we need to replace
        std::string new_val = std::to_string((int)eval(match));

        auto index = name.find("{" + match + "}");
        if (index == std::string::npos)
            continue;
        name = name.replace(index, match.length() + 2, new_val);
    }

    return name;
}


std::vector<uint8_t> Description::Memory::getBitmask()
{
    assert(size > 0);
    assert(offset < 8);

    std::vector<uint8_t> bytes((int)std::ceil(((double)size + (double)offset) / 8.0), 0xFF);

    int free_bytes = bytes.size() * 8 - (size + offset);
    uint8_t highest_byte_mask =  ((1 << (8-free_bytes))-1); 
    uint8_t lowest_byte_mask =~((1 << (offset))-1);

    bytes[0] &= lowest_byte_mask;
    bytes[bytes.size()-1] &= highest_byte_mask;

    return bytes;
}

Description::Memory::Memory(std::string key, YAML::Node config, std::vector<int> dimension)
{
    auto info = getDimension(key);
    name = getName(info.first, dimension);
    int dim = info.second;

    if (config.IsScalar())
    {
        size = config.as<int>();
        return;
    }

    for (YAML::const_iterator it = config.begin(); it != config.end(); ++it)
    {
        for (int i = 0; i < dim; i++)
        {
            std::vector<int> copy(dimension);
            copy.push_back(i);
            std::string n = getName(it->first.as<std::string>(), copy);
            Memory m(n, it->second, copy);
            size += m.size;
            submemory.push_back(m);
        }
    }
}