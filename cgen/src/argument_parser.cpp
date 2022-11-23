#include "argument_parser.hpp"
#include "generator.hpp"
#include <iostream>
ArgumentParser::ArgumentParser(int argc_, char **argv_)
{
    argc = argc_;
    argv = argv_;

    if(cmdOptionExists("--help") || cmdOptionExists("-h"))
        printHelp();

}

void ArgumentParser::printHelp()
{
    std::cout << "cgen - CPU Emulation Generator\n"
    "Options:\n"
    "--file, -f\t\tLocation of CPU Description File\n"
    "--out, -o\t\tLocation of the folder to wrote to\n";

    exit(0);
}

char* ArgumentParser::getCmdOption(const std::string &option)
{
    char ** itr = std::find(argv, argv + argc, option);
    if (itr != argv + argc && ++itr != argv + argc)
    {
        return *itr;
    }
    return 0;
}
bool ArgumentParser::cmdOptionExists(const std::string &option)
{
    return std::find(argv, argv + argc, option) != argv + argc;
}
std::string ArgumentParser::getIn()
{
    if(cmdOptionExists("--file"))
        return getCmdOption("--file");

    if(cmdOptionExists("-f"))
        return getCmdOption("-f");

    std::cerr << "No CPU Description file provided\n";
    exit(0);
}

std::string ArgumentParser::getOut()
{
    if(cmdOptionExists("--out"))
        return getCmdOption("--out");

    if(cmdOptionExists("-o"))
        return getCmdOption("-o");

    std::cerr << "No output specified\n";
    exit(0);
}

std::string ArgumentParser::getMode()
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