#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(Arduino);

void ArduinoGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    generateStandard(cpu, out);
    copyResource("fbitset", out);
    copyResource("scripts", out);
    copyResource("settings", out,
        {
            {"\\$\\{BITSET\\}", "FBITSET"}, 
            {"\\$\\{NO_PRINT_COMMENT\\}", ""},
            {"\\$\\{NO_CPPSTD_COMMENT\\}", ""}
        });

    copyResource("arduino", out,{{"\\$\\{CPU_NAME\\}", cpu.getName()}});

    createFile(out / "CMakeLists.txt", cpu.generateCMakeFile());
    createFile(out / "run.sh", cpu.generateRunScript());
}