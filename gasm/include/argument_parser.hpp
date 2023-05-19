#pragma once
#include <string>

// A class for parsing the argument vector from the CLI
class ArgumentParser
{
    public: 
    ArgumentParser(int argc, char **argv); // init with arguments
    std::string getCode(); // get path to assembler code
    std::string getCPU(); // get path to cdf
    std::string getOut(); // get path to write to
    std::string getFormat(); // get format to write in (bin or hex)
    void printHelp(); // print help for the options above

    private:
    char *getCmdOption(const std::string &option); // get specific option
    bool cmdOptionExists(const std::string &option); // check if option exists

    int argc; // argument count
    char **argv; // argument vector
};