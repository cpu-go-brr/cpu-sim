#include <iostream>
#include "cpu.hpp"

#define PATH "test_files/intel4004.yaml"


int main(int argc, char **argv)
{
    std::cout << PATH << "\n";
    auto desc = Description::CPU(PATH);
    desc.generate();

    return 0;
}