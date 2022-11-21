#include "generator/src_generator.hpp"
#include <fstream>

void srcGenerator::generate(Description::CPU cpu, std::filesystem::path out)
{
    std::filesystem::create_directories(out);

    generateStandard(cpu, out);
    std::filesystem::copy("resources/abitset", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy("resources/fbitset", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);

    std::ofstream settings(out / ("include/settings.hpp"), std::ios::trunc);
    settings << "#pragma once\n"
                "\n"
                "// Define used bitset (ABITSET, FBITSET)\n"
                "#define ABITSET\n"
                "\n"
                "// Mute all prints\n"
                "// #define NO_PRINT\n"
                "// #define NO_CPPSTD\n";
    settings.close();
}