#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(Arduino);

void ArduinoGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    //generate Standard files
    generateStandard(cpu, out);

    //include the fast bitset, scripts and settings
    copyResource("fbitset", out);
    copyResource("scripts", out);
    copyResource("settings", out,
        {
            {"\\$\\{BITSET\\}", "FBITSET"},         //set the value to Fast bitset
            {"\\$\\{NO_PRINT_COMMENT\\}", ""},      //remove cpp and print
            {"\\$\\{NO_CPPSTD_COMMENT\\}", ""}
        });

    //copy arduino specific files
    copyResource("arduino", out,{{"\\$\\{CPU_NAME\\}", cpu.getName()}});

    //create a CMake and a run.sh
    createFile(out / "CMakeLists.txt", cpu.generateCMakeFile());
    createFile(out / "run.sh", cpu.generateRunScript());

    //give execute permissions
    std::filesystem::permissions(out / "run.sh",std::filesystem::perms::owner_exec,std::filesystem::perm_options::add);
    std::filesystem::permissions(out / "build.sh",std::filesystem::perms::owner_exec,std::filesystem::perm_options::add);
}