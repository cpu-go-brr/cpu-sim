#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(PC);

void PCGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    std::filesystem::create_directories(out);

    generateStandard(cpu, out);
    std::filesystem::copy("resources/abitset", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy("resources/scripts", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);

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

    std::ofstream main(out / "src/main.cpp", std::ios::trunc);

    main << "#include \"" + cpu.getName() + ".hpp\"\n"
                                       "int main (int argc, char** argv)\n"
                                       "{\n" +
                cpu.getName() + " cpu;\n"
                           "return 0;\n"
                           "}\n";

    main.close();

    std::ofstream cmake(out / "CMakeLists.txt", std::ios::trunc);
    cmake << cpu.generateCMakeFile();
    cmake.close();

    std::ofstream run(out / ("run.sh"), std::ios::trunc);
    run << cpu.generateRunScript();
    run.close();
}