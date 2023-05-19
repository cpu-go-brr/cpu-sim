#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(PC);

void PCGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    //generate standard files
    generateStandard(cpu, out);
    
    //give both bitsets
    copyResource("abitset", out);
    copyResource("fbitset", out);

    //create run and build script
    copyResource("scripts", out,{{"\\$\\{CPU_NAME\\}", cpu.getLowerName()}});

    //allow print and cpp std libary
    copyResource("settings", out,
        {
            {"\\$\\{BITSET\\}", "ABITSET"}, 
            {"\\$\\{NO_PRINT_COMMENT\\}", "//"},
            {"\\$\\{NO_CPPSTD_COMMENT\\}", "//"}
        });

    //copy pc ressources
    copyResource("pc", out,{{"\\$\\{CPU_NAME\\}", cpu.getName()}});

    //generate cmake
    createFile(out / "CMakeLists.txt", cpu.generateCMakeFile());

    //give oermissions
    std::filesystem::permissions(out / "run.sh",std::filesystem::perms::owner_exec,std::filesystem::perm_options::add);
    std::filesystem::permissions(out / "build.sh",std::filesystem::perms::owner_exec,std::filesystem::perm_options::add);
}