#include "argument_parser.hpp"
#include "generator.hpp"
#include <iostream>
ArgumentParser::ArgumentParser(const int argc_, const char **argv_) : argc{argc_}, argv{argv_}
{
    //print help if --help or -h are specified
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
    //find option or return 0
    const char ** itr = std::find(argv, argv + argc, option);
    if (itr != argv + argc && ++itr != argv + argc)
    {
        return *itr;
    }
    return 0;
}
bool ArgumentParser::cmdOptionExists(const std::string &option) const
{
    //test if find reaches end of arguments
    return std::find(argv, argv + argc, option) != argv + argc;
}
std::string ArgumentParser::getInputPath() const
{
    //test if --file is specified
    if(cmdOptionExists("--file"))
        return getCmdOption("--file");

    //test if -f is specified
    if(cmdOptionExists("-f"))
        return getCmdOption("-f");

    //throw error and terminate
    std::cerr << "No CPU Description file provided\n";
    exit(0);
}

std::string ArgumentParser::getOutputPath() const
{
    //test if out file  is specified
    if(cmdOptionExists("--out"))
        return getCmdOption("--out");

    if(cmdOptionExists("-o"))
        return getCmdOption("-o");

    //throw error and terminate
    std::cerr << "No output specified\n";
    exit(0);
}

std::string ArgumentParser::getSelectedMode() const
{
    //search modes
    std::string mode = "";
    if(cmdOptionExists("--mode"))
        mode =  getCmdOption("--mode");

    else if(cmdOptionExists("-m"))
        mode =  getCmdOption("-m");
    
    if(mode == "")
    {
        //no mode specified --> throw error and terminate
        std::cerr << "No mode specified! Available Modes are:" <<std::endl;
        for(auto [key,pointer]: generators) std::cerr << "- "<< key << std::endl;
        exit(0);
    }

    if(!generators.contains(mode))
    {
        //wrong mode specified --> throw error and terminate
        std::cerr << "specified mode \""+mode+"\" does not exist! Available Modes are:" <<std::endl;
        for(auto [key,pointer]: generators) std::cerr << "- "<< key << std::endl;
        exit(0);
    }

    return mode;
}