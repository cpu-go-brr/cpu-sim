#pragma once
#include <string>
#include <map>
#include "cpu.hpp"
#include <filesystem>

typedef void (*Generator)(Description::CPU, std::filesystem::path);
inline std::map<std::string, Generator> generators = {};
void generateStandard(Description::CPU cpu, std::filesystem::path path);


#define ADD_GENERATOR(VAR) class VAR##Generator\
    {                                                            \
        friend class VAR##GeneratorInitializer;                  \
        struct VAR##GeneratorInitializer{                        \
            VAR##GeneratorInitializer(){                         \
                generators[#VAR] = generate;                     \
    }                                                            \
    }                                                            \
    ;                                                            \
    static VAR##GeneratorInitializer init;                       \
                                                                 \
    static void generate(Description::CPU cpu, std::filesystem::path out); \
    }                                                            \
    ;                                                            \
    VAR##Generator::VAR##GeneratorInitializer VAR##Generator::init;

