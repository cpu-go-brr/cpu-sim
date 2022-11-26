#pragma once
#include <string>

class ArgumentParser
{
public:
    ArgumentParser(int argc, char **argv); // init with arguments
    std::string getInputPath();            // get CPU Description path
    std::string getOutputPath();           // get Path to write to
    std::string getSelectedMode();         // get the seleted mode

private:
    void printHelp(); // print help screen

    bool cmdOptionExists(const std::string &option); // check if argument was specified
    char *getCmdOption(const std::string &option);   // retrieve specified argument

    int argc;    // argument count
    char **argv; // argument vector
};