#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(src);

void srcGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    generateStandard(cpu, out);

    copyResource("abitset", out);
    copyResource("fbitset", out);

    copyResource("settings", out,
        {
            {"\\$\\{BITSET\\}", "ABITSET"}, 
            {"\\$\\{NO_PRINT_COMMENT\\}", "//"},
            {"\\$\\{NO_CPPSTD_COMMENT\\}", "//"}
        });
}   