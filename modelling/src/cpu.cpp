#include "cpu.hpp"
#include "matheval.hpp"
#include <iostream>
#include <assert.h>
#include <regex>
#include <cmath>
#include <cctype>

Description::CPU::CPU(std::string path)
{

    auto file = YAML::LoadFile(path);

    name = file["name"].as<std::string>();
    description = file["description"].as<std::string>("");
    display = file["display"].as<std::string>("");

    auto mem = file["memory"]["internal"];
    for (YAML::const_iterator it = mem.begin(); it != mem.end(); ++it)
    {
        InternalMemory m(it->first.as<std::string>(), it->second, total_mem);
        total_mem += m.size;
        internal_memory.push_back(m);
    }

    mem = file["memory"]["external"];
    for (YAML::const_iterator it = mem.begin(); it != mem.end(); ++it)
    {
        ExternalMemory m(it->first.as<std::string>(), it->second);
        external_memory.push_back(m);
    }

    auto ins = file["instructions"];
    for (YAML::const_iterator it = ins.begin(); it != ins.end(); ++it)
    {
        Instruction m(it->first.as<std::string>(), it->second);
        instructions.push_back(m);
    }

    fetch = Instruction("fetch", file["fetch"]);


    // for (auto m : memory)
    // {
    //     std::cout << m.name << ":" << (m.byteoffset * 8 + m.bitoffset) << "\n";
    //     for (auto m2 : m.submemory)
    //     {
    //         std::cout << m2.name << ":" << (m2.byteoffset * 8 + m2.bitoffset) << "\n";
    //         for (auto m3 : m2.submemory)
    //             std::cout << m3.name << ":" << (m3.byteoffset * 8 + m3.bitoffset) << "\n";
    //     }
    // }
}
