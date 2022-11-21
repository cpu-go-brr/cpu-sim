#include <iostream>
#include "cpu.hpp"
#include "argument_parser.hpp"
#include "generator.hpp"

// #define PATH "test_files/intel4004.yaml"

int main(int argc, char **argv)
{
    ArgumentParser parser(argc, argv);
    auto in = parser.getIn();
    auto out = parser.getOut();
    auto mode = parser.getMode();
    
    // for(auto [key,pointer]: generators) std::cout << key << "\n";
    std::cout << "Building " <<in << " to " << out << "(" << mode << ")" << "\n";
    auto cpu = Description::CPU(in);
    generators[mode](cpu, out);
    // desc.generate(out);

    return 0;
}
