#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(Library);

void LibraryGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    generateStandard(cpu, out);

    copyResource("abitset", out);
    copyResource("fbitset", out);
    copyResource("scripts/build.sh", out);

    copyResource("settings", out,
    {
        {"\\$\\{BITSET\\}", "ABITSET"}, 
        {"\\$\\{NO_PRINT_COMMENT\\}", ""},
        {"\\$\\{NO_CPPSTD_COMMENT\\}", "//"}
    });

    copyFile("lib/cpu.pc.in", out/(cpu.getLowerName()+".pc.in"),{        
        {"\\$\\{CPU_NAME\\}", cpu.getName()}, 
        {"\\$\\{CPU_DESCRIPTION\\}", cpu.getDescription()}
        });

    copyFile("lib/CMakeLists", out/"CMakeLists",{{"\\$\\{CPU_NAME\\}", cpu.getLowerName()}});

    std::filesystem::permissions(out / "build.sh",std::filesystem::perms::owner_exec,std::filesystem::perm_options::add);

}