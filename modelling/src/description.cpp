#include "yaml-cpp/yaml.h"
#include "../include/description.hpp"
#include <iostream>
#include <regex>

Description::CPU::CPU(std::string path)
{
    auto file = YAML::LoadFile(path);

    name = file["name"].as<std::string>();
    description = file["description"].as<std::string>();

    auto mem = file["memory"];

    // mem is sequence
    for (YAML::const_iterator it = mem.begin(); it != mem.end(); ++it)
        memory.push_back(Memory(it->first.as<std::string>(), it->second));

    for (const auto &m : memory)
    {
        std::cout <<  "(" << m.name << ") " << m.size << "\n";
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
        return {matches[1], 1};

    return {matches[1], parseNumber(matches[2])};
}

std::string getName(std::string name, std::vector<int> dimensions)
{
    int i = 0;
    for (const auto &dims : dimensions)
    {
        std::regex r("$" + std::to_string(i));
        // write the results to an output iterator
        std::regex_replace(name, r, std::to_string(dims));
        i++;
    }
    return name;
}

Description::Memory::Memory(std::string key, YAML::Node config, std::vector<int> dimension)
{
    auto info = getDimension(key);
    name = getName(info.first, dimension);
    int dim = info.second;
    if (dim > 1)
        dimension.push_back(dim);

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
            copy.push_back(dim);
            Memory m(it->first.as<std::string>(), it->second, copy);
            size += m.size;
            submemory.push_back(m);
        }
    }
}