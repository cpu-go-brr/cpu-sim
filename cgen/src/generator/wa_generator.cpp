#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(WebAssembly);

void WebAssemblyGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    //generate standard
    generateStandard(cpu, out/"wa");

    //copy th yaml into the dirctory for gasm
    std::filesystem::copy(cpu.getPath(), out/"wa/cpu.yaml");
    copyResource("gasm", out/"wa", 
        {
            {"\\$\\{INSTRUCTION_CODES\\}", cpu.generateInstructionCodeMap()}
        });

    //Give both bitsets
    copyResource("abitset", out/"wa");
    copyResource("fbitset", out/"wa");

    //use fast bitset, allow printing and cpp stdlib
    copyResource("settings", out/"wa",
        {
            {"\\$\\{BITSET\\}", "FBITSET"}, 
            {"\\$\\{NO_PRINT_COMMENT\\}", "//"},
            {"\\$\\{NO_CPPSTD_COMMENT\\}", "//"}
        });

    //copy the website
    copyResource("website_common", out, 
    {
        {"\\$\\{CPU_NAME\\}", cpu.getName()}, 
        {"\\$\\{BACKEND_SCRIPTS\\}", "<script src=\"js/cpu.js\" defer></script><script src=\"js/cpu_init.js\" defer></script>"}
    });

    //copy the webassembly

    copyResource("website_wa", out,
    {
        {"\\$\\{CPU_NAME\\}", cpu.getName()}, 
    });

    //generate cpu display config
    createFile(out/"cpu.json", cpu.generateDisplayJSONInfo());

    //generate syntax highlighting for the ace editor in the website
    createFile(out/"js/ace/mode-general_assembly.js", cpu.generateSyntaxHighlighter());

    //give the build script permissions
    std::filesystem::permissions(out / "build.sh",std::filesystem::perms::owner_exec,std::filesystem::perm_options::add);
}   