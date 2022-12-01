#pragma once
#include <string>
#include <map>
#include <filesystem>
#include "cpu.hpp"

//function pointer to a source code generator
typedef void (*Generator)(CPUDescription::CPU, std::filesystem::path);
//a map of source code generators
inline std::map<std::string, Generator> generators = {};

//a function to generate common files used in all generators
void generateStandard(CPUDescription::CPU cpu, std::filesystem::path path);


//Makro to automatically generate Generator class and add it into the generator Map
#define ADD_GENERATOR(VAR)                                                        \
    class VAR##Generator                                                          \
    {                                                                             \
        friend class VAR##GeneratorInitializer;                                   \
        struct VAR##GeneratorInitializer                                          \
        {                                                                         \
            VAR##GeneratorInitializer()                                           \
            {                                                                     \
                generators[#VAR] = generate;                                      \
            }                                                                     \
        };                                                                        \
        static VAR##GeneratorInitializer init;                                    \
                                                                                  \
        static void generate(CPUDescription::CPU cpu, std::filesystem::path out); \
    };                                                                            \
    VAR##Generator::VAR##GeneratorInitializer VAR##Generator::init;
