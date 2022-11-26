#include "cpu.hpp"
#include "matheval.hpp"
#include <iostream>
#include <assert.h>
#include <regex>
#include <cmath>
#include <cctype>


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

std::string CPUDescription::InternalMemory::getJSONDescription()
{
    if(submemory.size() == 0)
    return "\"\\\"" + name + "\\\":{\\\"bits\\\":"+std::to_string(size)+",\\\"val\\\":\" + std::to_string(get("+name+").val()) + \"},\"";

    std::string ret = "\"\\\"" + name + "\\\":{\"\n";
        for(auto s: submemory)
            ret += s.getJSONDescription() + "\n";
    
    ret = ret.substr(0,ret.size()-3) + "\"\n";
    return ret +"\"},\"";
}


std::vector<uint8_t> CPUDescription::InternalMemory::getBitmask()
{
    assert(size > 0);

    std::vector<uint8_t> bytes((int)std::ceil(((double)size + (double)bitoffset) / 8.0), 0xFF);

    int free_bytes = bytes.size() * 8 - (size + bitoffset);
    uint8_t highest_byte_mask = ((1 << (8 - free_bytes)) - 1);
    uint8_t lowest_byte_mask = ~((1 << (bitoffset)) - 1);

    bytes[0] &= lowest_byte_mask;
    bytes[bytes.size() - 1] &= highest_byte_mask;

    return bytes;
}


std::map<std::string, std::size_t> CPUDescription::InternalMemory::address_lengths = {};

CPUDescription::InternalMemory::InternalMemory(std::string key, YAML::Node config, int total_mem, std::vector<int> dimension)
{
    auto info = getDimension(key);
    name = getName(info.first, dimension);
    int dim = info.second;

    if (config.IsScalar())
    {
        size = config.as<int>();
    }

    for (YAML::const_iterator it = config.begin(); it != config.end(); ++it)
    {
        for (int i = 0; i < dim; i++)
        {
            std::vector<int> copy(dimension);
            copy.push_back(i);
            std::string n = getName(it->first.as<std::string>(), copy);
            InternalMemory m(n, it->second, total_mem + size, copy);
            size += m.size;
            submemory.push_back(m);
        }
    }

    bitoffset = total_mem % 8;
    byteoffset = total_mem / 8;
    InternalMemory::address_lengths[name] = size;
}