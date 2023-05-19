#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(Library);

void LibraryGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    //generate Standard files
    generateStandard(cpu, out);

    //give both bitsets
    copyResource("abitset", out);
    copyResource("fbitset", out);
    copyResource("scripts/build.sh", out); //copy the build script

    //set settings to accurate Bitset and remove prints but allow cpp
    copyResource("settings", out,
    {
        {"\\$\\{BITSET\\}", "ABITSET"}, 
        {"\\$\\{NO_PRINT_COMMENT\\}", ""},
        {"\\$\\{NO_CPPSTD_COMMENT\\}", "//"}
    });

    // create lib description

    copyFile("lib/cpu.pc.in", out/(cpu.getLowerName()+".pc.in"),{        
        {"\\$\\{CPU_NAME\\}", cpu.getName()}, 
        {"\\$\\{CPU_DESCRIPTION\\}", cpu.getDescription()}
        });

    //create cmake
    copyFile("lib/CMakeLists", out/"CMakeLists",{{"\\$\\{CPU_NAME\\}", cpu.getLowerName()}});

    //give execute permission to build script
    std::filesystem::permissions(out / "build.sh",std::filesystem::perms::owner_exec,std::filesystem::perm_options::add);

}