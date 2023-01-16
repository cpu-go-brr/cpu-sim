#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(WebAssembly);

void WebAssemblyGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{

    generateStandard(cpu, out/"wa");

    std::filesystem::copy(cpu.getPath(), out/"wa/cpu.yaml");
    copyResource("gasm", out/"wa");
    copyResource("abitset", out/"wa");
    copyResource("fbitset", out/"wa");

    copyResource("settings", out/"wa",
        {
            {"\\$\\{BITSET\\}", "ABITSET"}, 
            {"\\$\\{NO_PRINT_COMMENT\\}", "//"},
            {"\\$\\{NO_CPPSTD_COMMENT\\}", "//"}
        });

    copyResource("website_common", out, 
    {
        {"\\$\\{CPU_NAME\\}", cpu.getName()}, 
        {"\\$\\{BACKEND_SCRIPTS\\}", "<script src=\"js/cpu.js\" defer></script><script src=\"js/cpu_init.js\" defer></script>"}
    });

    copyResource("website_wa", out,
    {
        {"\\$\\{CPU_NAME\\}", cpu.getName()}, 
    });

    createFile(out/"cpu.json", cpu.generateDisplayJSONInfo());
    createFile(out/"js/ace/mode-general_assembly.js", cpu.generateSyntaxHighlighter());

}   