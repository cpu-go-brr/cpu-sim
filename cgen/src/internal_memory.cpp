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

    const std::regex r(".*\\{(.+)\\}.*");
    std::smatch matches;

    while (std::regex_match(name, matches, r))
    {
        std::string match = matches[1].str(); // string we need to replace
        std::string new_val = std::to_string((std::size_t)MathExpression::eval(match));


        auto index = name.find("{" + match + "}");
        if (index == std::string::npos)
            continue;
        name = name.replace(index, match.length() + 2, new_val);
    }

    return name;
}

std::string CPUDescription::InternalMemory::getUpperName() const
{
    
    std::string uppername = name;
    std::for_each(uppername.begin(), uppername.end(), [](char &c)
                  { c = std::toupper(c); });

    return uppername;
}

std::vector<std::string> CPUDescription::InternalMemory::getNames() const
{
    std::vector<std::string> ret{getUpperName()};

    for(auto& m : submemory)
    {
        auto names = m.getNames();
        ret.insert(ret.end(),names.begin(), names.end());
    }
    return ret;
}


std::string CPUDescription::InternalMemory::getJSONDescription()
{
    //if we have no submemry simplay write information
    if(submemory.size() == 0)
        return "\"\\\"" + name + "\\\":{\\\"bits\\\":"+std::to_string(size)+",\\\"val\\\":\" + std::to_string(get("+name+").val()) + \"},\"";

    //else return for every child information
    std::string ret = "\"\\\"" + name + "\\\":{\"\n";
        for(auto s: submemory)
            ret += s.getJSONDescription() + "\n";
    
    ret = ret.substr(0,ret.size()-3) + "\"\n";
    return ret +"\"},\"";
}


std::size_t CPUDescription::InternalMemory::getSize() const
{
    return size;
}

std::string CPUDescription::InternalMemory::getAddressInfo() const
{
    //return information for every address info + children
    std::string ret = "const AddressInfo " + name + "{" + std::to_string(byteoffset) + ", " + std::to_string(bitoffset) + ", " + std::to_string(size) + "};\n";
    for (auto mem : submemory)
        ret += mem.getAddressInfo();
    return ret;
}


std::map<std::string, std::size_t> CPUDescription::InternalMemory::address_lengths = {};

CPUDescription::InternalMemory::InternalMemory(std::string key, YAML::Node config, int total_mem, std::vector<int> dimension)
{
    //get dimensions by squared brackets f.E. abc[3] --> 3 
    auto info = getDimension(key);
    name = getName(info.first, dimension);
    int dim = info.second;

    if (config.IsScalar())          //abc: 3
        size = config.as<int>();
    

    //init all submemoy
    for (YAML::const_iterator it = config.begin(); it != config.end(); ++it)
    {
        //for every dimension
        for (int i = 0; i < dim; i++)
        {
            std::vector<int> copy(dimension);
            copy.push_back(i);
            std::string name = getName(it->first.as<std::string>(), copy);
            InternalMemory mem(name, it->second, total_mem + size, copy);
            size += mem.size;   //increase memory size counter
            submemory.push_back(mem);
        }
    }


    bitoffset = total_mem % 8;
    byteoffset = total_mem / 8;
    InternalMemory::address_lengths[name] = size; //increase memory size counter
}