#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(PC);

void PCGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    generateStandard(cpu, out);
    
    copyResource("abitset", out);
    copyResource("scripts", out,{{"\\$\\{CPU_NAME\\}", cpu.getLowerName()}});

    copyResource("settings", out,
        {
            {"\\$\\{BITSET\\}", "ABITSET"}, 
            {"\\$\\{NO_PRINT_COMMENT\\}", "//"},
            {"\\$\\{NO_CPPSTD_COMMENT\\}", "//"}
        });

    copyResource("pc", out,{{"\\$\\{CPU_NAME\\}", cpu.getName()}});

    createFile(out / "CMakeLists.txt", cpu.generateCMakeFile());
}