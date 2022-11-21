#include "generator/arduino_generator.hpp"
#include <fstream>

void ArduinoGenerator::generate(Description::CPU cpu, std::filesystem::path out)
{
    std::filesystem::create_directories(out);

    generateStandard(cpu, out);
    std::filesystem::copy("resources/fbitset", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy("resources/scripts", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);

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
            "#include <Arduino.h>"
            "#include \"" +
                cpu.name + ".hpp\""
                           "void setup()"
                           "{"
                           "// put your setup code here, to run once:"
                           "Serial.begin(9600);"
                           "while(!Serial.available());"
                           "}"
                           "" +
                cpu.name + " cpu{};"
                           ""
                           "void loop()"
                           "{"
                           "bitset prog[] = {0x00}; "
                           "cpu.flash_rom(prog, sizeof(prog) / sizeof(bitset));"
                           "cpu.simulate(1);"
                           "cpu.display();"
                           "    "
                           "exit(0);"
                           ""
                           "}";
    main.close();

    std::ofstream cmake(out / "CMakeLists.txt", std::ios::trunc);
    cmake << cpu.generateCMakeFile();
    cmake.close();

    std::ofstream run(out / ("run.sh"), std::ios::trunc);
    run << cpu.generateRunScript();
    run.close();
}