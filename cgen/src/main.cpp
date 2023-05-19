#include <iostream>
#include "cpu.hpp"
#include "argument_parser.hpp"
#include "generator.hpp"

int main(const int argc, const char **argv)
{
    //start parsing arguments
    ArgumentParser parser(argc, argv);
    auto in = parser.getInputPath();
    auto out = parser.getOutputPath();
    auto mode = parser.getSelectedMode();

    //get parameter
    
    std::cout << "Building " <<in << " to " << out << "(" << mode << ")" << std::endl;
    auto cpu = CPUDescription::CPU(in);
    //read cpu from input
    std::filesystem::create_directories(out);

    //build cpu
    generators[mode](cpu, out);

    return 0;
}
