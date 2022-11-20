#include "cpu.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cmath>




void generateStandard(Description::CPU cpu, std::filesystem::path out)
{
    std::filesystem::copy("resources/standard", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);

    std::ofstream hpp(out/("include/" + cpu.name + ".hpp"), std::ios::trunc);
    hpp << cpu.generateHpp();
    hpp.close();

    std::ofstream info(out/"include/AddressInfos.hpp", std::ios::trunc);
    info << cpu.generateAddressInfos();
    info.close();

    std::ofstream cpp(out/("src/" + cpu.name + ".cpp"), std::ios::trunc);
    cpp << cpu.generateCpp();
    cpp.close();
}