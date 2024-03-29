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

//creates a file with given content
void createFile(const std::filesystem::path& path, const std::string content);

//copys a file with given repklacements
void copyFile(const std::filesystem::path &from, const std::filesystem::path &to, const std::vector<std::pair<std::string, std::string>> &replacements);

//copys a ressource relative to the ressources folder to given path 
void copyResource(const std::string& resource, const std::filesystem::path& to);

//copys a ressource relative to the ressources folder to given path with text replacements
void copyResource(const std::string& resource, const std::filesystem::path& to, const std::vector<std::pair<std::string, std::string>>& replacements);

//gets the path of the executable
std::filesystem::path getExecutablePath();


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
