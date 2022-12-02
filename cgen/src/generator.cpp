#include "cpu.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cmath>


std::filesystem::path getExecutablePath()
{
    return std::filesystem::canonical("/proc/self/exe").parent_path();
}


void generateStandard(CPUDescription::CPU cpu, std::filesystem::path out)
{
    std::filesystem::copy(getExecutablePath()/"resources/standard", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);

    std::ofstream hpp(out/("include/" + cpu.getName() + ".hpp"), std::ios::trunc);
    hpp << cpu.generateHpp();
    hpp.close();

    std::ofstream info(out/"include/AddressInfos.hpp", std::ios::trunc);
    info << cpu.generateAddressInfos();
    info.close();

    std::ofstream cpp(out/("src/" + cpu.getName() + ".cpp"), std::ios::trunc);
    cpp << cpu.generateCpp();
    cpp.close();
}