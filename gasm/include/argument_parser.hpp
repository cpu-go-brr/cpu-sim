#pragma once
#include <string>

class ArgumentParser
{
    public: 
    ArgumentParser(int argc, char **argv);
    std::string getCode();
    std::string getCPU();
    std::string getOut();
    std::string getFormat();
    void printHelp();

    private:
    char *getCmdOption(const std::string &option);
    bool cmdOptionExists(const std::string &option);

    int argc;
    char **argv;
};