#include <iostream>
#include "cpu.hpp"
#include "argument_parser.hpp"
#include "generator.hpp"

int main(const int argc, const char **argv)
{
    ArgumentParser parser(argc, argv);
    auto in = parser.getInputPath();
    auto out = parser.getOutputPath();
    auto mode = parser.getSelectedMode();
    
    std::cout << "Building " <<in << " to " << out << "(" << mode << ")" << std::endl;
    auto cpu = CPUDescription::CPU(in);

    std::filesystem::create_directories(out);
    generators[mode](cpu, out);

    return 0;
}
