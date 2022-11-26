#include <iostream>
#include "cpu.hpp"
#include "argument_parser.hpp"
#include "generator.hpp"

// #define PATH "test_files/intel4004.yaml"

int main(int argc, char **argv)
{
    std::cout << argv[0] << std::endl;

    ArgumentParser parser(argc, argv);
    auto in = parser.getInputPath();
    auto out = parser.getOutputPath();
    auto mode = parser.getSelectedMode();
    
    // for(auto [key,pointer]: generators) std::cout << key << "\n";
    std::cout << "Building " <<in << " to " << out << "(" << mode << ")" << std::endl;
    auto cpu = CPUDescription::CPU(in);

    std::filesystem::create_directories(out);
    generators[mode](cpu, out);
    // desc.generate(out);

    return 0;
}
