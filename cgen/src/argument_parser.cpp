#include "argument_parser.hpp"
#include "generator.hpp"
#include <iostream>
ArgumentParser::ArgumentParser(const int argc_, const char **argv_) : argc{argc_}, argv{argv_}
{
    if(cmdOptionExists("--help") || cmdOptionExists("-h"))
        printHelpAndExit();
}

void ArgumentParser::printHelpAndExit() const
{
    std::cout << "cgen - CPU Emulation Generator\n"
    "Options:\n"
    "--file, -f\t\tLocation of CPU Description File\n"
    "--out, -o\t\tLocation of the folder to wrote to\n";

    exit(0);
}

const char* ArgumentParser::getCmdOption(const std::string &option) const
{
    const char ** itr = std::find(argv, argv + argc, option);
    if (itr != argv + argc && ++itr != argv + argc)
    {
        return *itr;
    }
    return 0;
}
bool ArgumentParser::cmdOptionExists(const std::string &option) const
{
    return std::find(argv, argv + argc, option) != argv + argc;
}
std::string ArgumentParser::getInputPath() const
{
    if(cmdOptionExists("--file"))
        return getCmdOption("--file");

    if(cmdOptionExists("-f"))
        return getCmdOption("-f");

    std::cerr << "No CPU Description file provided\n";
    exit(0);
}

std::string ArgumentParser::getOutputPath() const
{
    if(cmdOptionExists("--out"))
        return getCmdOption("--out");

    if(cmdOptionExists("-o"))
        return getCmdOption("-o");

    std::cerr << "No output specified\n";
    exit(0);
}

std::string ArgumentParser::getSelectedMode() const
{
    std::string mode = "";
    if(cmdOptionExists("--mode"))
        mode =  getCmdOption("--mode");

    else if(cmdOptionExists("-m"))
        mode =  getCmdOption("-m");
    
    if(mode == "")
    {
        std::cerr << "No mode specified! Available Modes are:" <<std::endl;
        for(auto [key,pointer]: generators) std::cerr << "- "<< key << std::endl;
        exit(0);
    }

    if(!generators.contains(mode))
    {
        std::cerr << "specified mode \""+mode+"\" does not exist! Available Modes are:" <<std::endl;
        for(auto [key,pointer]: generators) std::cerr << "- "<< key << std::endl;
        exit(0);
    }

    return mode;
}