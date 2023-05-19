#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(src);

void srcGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    //generate standard
    generateStandard(cpu, out);

    //give both bitsets
    copyResource("abitset", out);
    copyResource("fbitset", out);

    //set accurate bitset to default und allow printing and cpp std library
    copyResource("settings", out,
        {
            {"\\$\\{BITSET\\}", "ABITSET"}, 
            {"\\$\\{NO_PRINT_COMMENT\\}", "//"},
            {"\\$\\{NO_CPPSTD_COMMENT\\}", "//"}
        });
}   