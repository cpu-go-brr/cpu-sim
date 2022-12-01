#pragma once
#include <string>

class ArgumentParser
{
public:
    ArgumentParser(const int argc, const char **argv); // init with arguments
    std::string getInputPath() const;            // get CPU Description path
    std::string getOutputPath() const;           // get Path to write to
    std::string getSelectedMode() const;         // get the seleted mode

private:
    void printHelpAndExit() const; // print help screen

    bool cmdOptionExists(const std::string &option) const; // check if argument was specified
    const char* getCmdOption(const std::string &option) const;   // retrieve specified argument

    const int argc;    // argument count
    const char **argv; // argument vector
};