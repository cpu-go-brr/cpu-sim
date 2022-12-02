#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(Arduino);

void ArduinoGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    generateStandard(cpu, out);
    std::filesystem::copy(getExecutablePath()/"resources/fbitset", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy(getExecutablePath()/"resources/scripts", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);

    std::ofstream settings(out / ("include/settings.hpp"), std::ios::trunc);
    settings << "#pragma once\n"
                "\n"
                "// Define used bitset (ABITSET, FBITSET)\n"
                "#define FBITSET\n"
                "\n"
                "// Mute all prints\n"
                "#define NO_PRINT\n"
                "#define NO_CPPSTD\n";
    settings.close();

    std::ofstream main(out / "src/main.cpp", std::ios::trunc);

    main << ""
            "#include <Arduino.h>\n"
            "#include \"" +
                cpu.getName() + ".hpp\"\n"
                           "void setup()\n"
                           "{\n"
                           "// put your setup code here, to run once:\n"
                           "Serial.begin(9600);\n"
                           "while(!Serial.available());\n"
                           "}\n"
                           "\n" +
                cpu.getName() + " cpu{};\n"
                           ""
                           "void loop()\n"
                           "{\n"
                           "bitset prog[] = {0x00}; \n"
                           "cpu.flash_rom(prog, sizeof(prog) / sizeof(bitset));\n"
                           "cpu.simulate();\n"
                           "cpu.display();\n"
                           "    \n"
                           "exit(0);\n"
                           "\n"
                           "}\n";
    main.close();

    std::ofstream cmake(out / "CMakeLists.txt", std::ios::trunc);
    cmake << cpu.generateCMakeFile();
    cmake.close();

    std::ofstream run(out / ("run.sh"), std::ios::trunc);
    run << cpu.generateRunScript();
    run.close();
}