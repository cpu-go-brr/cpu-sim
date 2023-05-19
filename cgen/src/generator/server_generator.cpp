#include "generator.hpp"
#include <fstream>
#include <iostream>


ADD_GENERATOR(Server);

void ServerGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    //create directories for front and backend
    std::filesystem::create_directories(out/"server");
    std::filesystem::create_directories(out/"website");

    //copy the yaml into the backend
    std::filesystem::copy(cpu.getPath(), out/"server/cpu.yaml");
    //copy gasm to the backend
    copyResource("gasm", out/"server", 
        {
            {"\\$\\{INSTRUCTION_CODES\\}", cpu.generateInstructionCodeMap()}
        });

    //copy ressources
    generateStandard(cpu, out/"server");
    copyResource("abitset", out/"server");
    copyResource("server", out/"server", {{"\\$\\{CPU_NAME\\}", cpu.getName()}});
    copyResource("scripts", out/"server",{{"\\$\\{CPU_NAME\\}", cpu.getLowerName()}});
    copyResource("website_common", out/"website", 
    {
        {"\\$\\{CPU_NAME\\}", cpu.getName()}, 
        {"\\$\\{BACKEND_SCRIPTS\\}", "<script src=\"js/cpu_server.js\" defer></script>"}
    });
    copyResource("website_server", out/"website");

    //create a display config
    createFile(out/"website/cpu.json", cpu.generateDisplayJSONInfo());

    //generate syntax highlighting for the ace editor in the website
    createFile(out/"website/js/ace/mode-general_assembly.js", cpu.generateSyntaxHighlighter());

    //use the accurate bitset and remove printing
    copyResource("settings", out,
        {
            {"\\$\\{BITSET\\}", "ABITSET"}, 
            {"\\$\\{NO_PRINT_COMMENT\\}", "//"},
            {"\\$\\{NO_CPPSTD_COMMENT\\}", ""}
        });

    //create cmake
    createFile(out / "server/CMakeLists.txt", cpu.generateCMakeFile());

    //give execute permissions
    std::filesystem::permissions(out / "server/run.sh",std::filesystem::perms::owner_exec,std::filesystem::perm_options::add);
    std::filesystem::permissions(out / "server/build.sh",std::filesystem::perms::owner_exec,std::filesystem::perm_options::add);

}