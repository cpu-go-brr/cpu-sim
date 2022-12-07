#include "generator.hpp"
#include <fstream>
#include <iostream>


ADD_GENERATOR(Server);

void ServerGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    std::filesystem::create_directories(out/"server");
    std::filesystem::create_directories(out/"website");

    generateStandard(cpu, out/"server");
    std::filesystem::copy(getExecutablePath()/"resources/abitset", out/"server", std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy(getExecutablePath()/"resources/server", out/"server", std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy(getExecutablePath()/"resources/scripts", out/"server", std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy(getExecutablePath()/"resources/website_common", out/"website", std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy(getExecutablePath()/"resources/website_server", out/"website", std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);


    std::ofstream cpu_json(out / "website/cpu.json", std::ios::trunc);
    cpu_json << cpu.generateDisplayJSONInfo();
    cpu_json.close();

    std::ofstream syntaxHighlighting(out / "website/js/ace/mode-general_assembly.js", std::ios::trunc);
    syntaxHighlighting << cpu.generateSyntaxHightlighter();
    syntaxHighlighting.close();

    std::ofstream settings(out / "server/include/settings.hpp", std::ios::trunc);
    settings << "#pragma once\n"
                "\n"
                "// Define used bitset (ABITSET, FBITSET)\n"
                "#define ABITSET\n"
                "\n"
                "// Mute all prints\n"
                "#define NO_PRINT\n"
                "// #define NO_CPPSTD\n";
    settings.close();

    std::ofstream main(out / "server/src/main.cpp", std::ios::trunc);

    main << ""
            "#include \"httplib.hpp\"\n"
            "#include \"" +
                cpu.getName() + ".hpp\"\n"
                "void addCORS(const httplib::Request &req, httplib::Response &res)\n{\n    res.set_header(\"Access-Control-Allow-Origin\", req.get_header_value(\"Origin\").c_str());\n    res.set_header(\"Allow\", \"GET, POST, HEAD, OPTIONS\");\n    res.set_header(\"Access-Control-Allow-Headers\", \"X-Requested-With, Content-Type, Accept, Origin, Authorization\");\n    res.set_header(\"Access-Control-Allow-Methods\", \"OPTIONS, GET, POST, HEAD\");\n}\n"
                           "int main (int argc, char** argv)\n"
                           "{\n" +
                cpu.getName() + " cpu;\n"
                "    httplib::Server svr;\n"
                "svr.Get(\"/simulate\", [&](const httplib::Request &req, httplib::Response &res)\n"
    "{\n"
    "    cpu.simulate();\n"
        "addCORS(req,res);\n"
    "    res.set_content(\"\", \"\"); \n"
    "});\n"
"\n"
    "svr.Get(\"/get\", [&](const httplib::Request &req, httplib::Response &res)\n"
    "{\n"
        "addCORS(req,res);\n"
    "    res.set_content(cpu.json(), \"application/json\"); \n"
    "});\n"
    "svr.listen(\"0.0.0.0\", 8080);\n"
                           "return 0;\n"
                           "}\n";


    main.close();

    std::ofstream cmake(out / "server/CMakeLists.txt", std::ios::trunc);
    cmake << cpu.generateCMakeFile();
    cmake.close();

    std::ofstream run(out / ("server/run.sh"), std::ios::trunc);
    run << cpu.generateRunScript();
    run.close();



}