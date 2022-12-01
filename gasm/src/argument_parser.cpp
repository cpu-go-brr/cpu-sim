#include "argument_parser.hpp"
#include <iostream>
#include <algorithm>

ArgumentParser::ArgumentParser(int argc_, char **argv_)
{
    argc = argc_;
    argv = argv_;

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
std::string ArgumentParser::getCode()
{
    if(cmdOptionExists("--file"))
        return getCmdOption("--file");

    if(cmdOptionExists("-f"))
        return getCmdOption("-f");

    std::cerr << "No assembler file provided\n";
    exit(0);
}

std::string ArgumentParser::getCPU()
{
    if(cmdOptionExists("--cpu"))
        return getCmdOption("--cpu");

    if(cmdOptionExists("-c"))
        return getCmdOption("-c");

    std::cerr << "No cpu specified\n";
    exit(0);
}

std::string ArgumentParser::getOut()
{
    if(cmdOptionExists("--out"))
        return getCmdOption("--out");

    if(cmdOptionExists("-o"))
        return getCmdOption("-o");

    return "/dev/tty";
}


std::string ArgumentParser::getFormat()
{
    if(cmdOptionExists("--mode"))
        return getCmdOption("--mode");

    if(cmdOptionExists("-m"))
        return getCmdOption("-m");

    return "hex";
}

