#include "cpu.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cmath>
#include "generator.hpp"

std::filesystem::path getExecutablePath()
{
    //get oath of executable (Linux specific)

    return std::filesystem::canonical("/proc/self/exe").parent_path();
}

void generateStandard(CPUDescription::CPU cpu, std::filesystem::path out)
{
    //create some standard files for every cgen mode

    std::filesystem::create_directories(out);

    copyResource("standard", out);

    createFile(out / "include/AddressInfos.hpp", cpu.generateAddressInfos());

    createFile(out / ("include/" + cpu.getName() + ".hpp"), cpu.generateHpp());
    createFile(out / ("src/" + cpu.getName() + ".cpp"), cpu.generateCpp());
}

void copyResource(const std::string &resource, const std::filesystem::path &to)
{
    // copy relative to executable
    std::filesystem::copy(getExecutablePath() / ("resources/" + resource), to, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
}

void copyFile(const std::filesystem::path &from, const std::filesystem::path &to, const std::vector<std::pair<std::string, std::string>> &replacements)
{
    // copy file and replace
    std::ifstream input(from);
    std::string content((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));

    for(const auto& replacement : replacements)
        content = std::regex_replace(content, std::regex(replacement.first), replacement.second);

    createFile(to, content);
}

void copyResource(const std::string &resource, const std::filesystem::path &to, const std::vector<std::pair<std::string, std::string>> &replacements)
{
    // copy file and replace
    auto base_path = getExecutablePath() / ("resources/" + resource);
    for (const auto &file : std::filesystem::recursive_directory_iterator(base_path))
    {
        auto new_path = to / std::filesystem::relative(file.path(), base_path);
        if(file.is_directory()) 
            std::filesystem::create_directories(new_path);
        else
            copyFile(file.path(), new_path, replacements);
    }
}

void createFile(const std::filesystem::path &path, const std::string content)
{
    std::ofstream file(path, std::ios::trunc);
    file << content;
    file.close();
}