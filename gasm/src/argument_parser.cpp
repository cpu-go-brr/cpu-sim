#include "argument_parser.hpp"
#include <iostream>
#include <algorithm>

ArgumentParser::ArgumentParser(int argc_, char **argv_)
{
    argc = argc_;
    argv = argv_;
    
    // print help if --help or -h are specified
    if(cmdOptionExists("--help") || cmdOptionExists("-h"))
        printHelp();

}

void ArgumentParser::printHelp()
{
    std::cout << "gasm - General Assembler\n"
    "Options:\n"
    "--file, -f\t\tLocation of the Code\n"
    "--cpu, -c\t\tLocation of the CPU Description File\n"
    "--out, -o\t\tLocation of the Output File\n"
    "--mode, -m\t\tOutput Mode (bin, c, hex)\n";

    exit(0);
}

char* ArgumentParser::getCmdOption(const std::string &option)
{
    // find and return option or return 0
    char ** itr = std::find(argv, argv + argc, option);
    if (itr != argv + argc && ++itr != argv + argc)
    {
        return *itr;
    }
    return 0;
}
bool ArgumentParser::cmdOptionExists(const std::string &option)
{
    // check if option exists
    return std::find(argv, argv + argc, option) != argv + argc;
}
std::string ArgumentParser::getCode()
{
    // return path to assembler code if exists or exit
    if(cmdOptionExists("--file"))
        return getCmdOption("--file");

    if(cmdOptionExists("-f"))
        return getCmdOption("-f");

    // no path specified --> exit
    std::cerr << "No assembler file provided\n";
    exit(0);
}

std::string ArgumentParser::getCPU()
{
    // return path to cdf if exists or exit
    if(cmdOptionExists("--cpu"))
        return getCmdOption("--cpu");

    if(cmdOptionExists("-c"))
        return getCmdOption("-c");

    // no path specified --> exit
    std::cerr << "No cpu specified\n";
    exit(0);
}

std::string ArgumentParser::getOut()
{
    // return path to write to
    if(cmdOptionExists("--out"))
        return getCmdOption("--out");

    if(cmdOptionExists("-o"))
        return getCmdOption("-o");

    // no path specified --> default to /dev/stdout
    return "/dev/stdout";
}


std::string ArgumentParser::getFormat()
{
    // return mode to write in
    if(cmdOptionExists("--mode"))
        return getCmdOption("--mode");

    if(cmdOptionExists("-m"))
        return getCmdOption("-m");

    // no mode specified --> default to hex
    return "hex";
}

