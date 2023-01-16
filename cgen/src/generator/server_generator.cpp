#include "generator.hpp"
#include <fstream>
#include <iostream>


ADD_GENERATOR(Server);

void ServerGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    std::filesystem::create_directories(out/"server");
    std::filesystem::create_directories(out/"website");

    std::filesystem::copy(cpu.getPath(), out/"server/cpu.yaml");
    copyResource("gasm", out/"server");

    generateStandard(cpu, out/"server");
    copyResource("abitset", out/"server");
    copyResource("server", out/"server", {{"\\$\\{CPU_NAME\\}", cpu.getName()}});
    copyResource("scripts", out,{{"\\$\\{CPU_NAME\\}", cpu.getLowerName()}});
    copyResource("website_common", out/"website", 
    {
        {"\\$\\{CPU_NAME\\}", cpu.getName()}, 
        {"\\$\\{BACKEND_SCRIPTS\\}", "<script src=\"js/cpu_server.js\" defer></script>"}
    });
    copyResource("website_server", out/"website");

    createFile(out/"website/cpu.json", cpu.generateDisplayJSONInfo());
    createFile(out/"website/js/ace/mode-general_assembly.js", cpu.generateSyntaxHighlighter());

    copyResource("settings", out,
        {
            {"\\$\\{BITSET\\}", "ABITSET"}, 
            {"\\$\\{NO_PRINT_COMMENT\\}", "//"},
            {"\\$\\{NO_CPPSTD_COMMENT\\}", ""}
        });

    createFile(out / "server/CMakeLists.txt", cpu.generateCMakeFile());
}