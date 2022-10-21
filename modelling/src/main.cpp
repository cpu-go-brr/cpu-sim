#include <iostream>
#include "yaml-cpp/yaml.h"
#include "description.hpp"
#include "matheval.hpp"
#include "bitset.hpp"

#define PATH "test_files/intel4004.yaml"

#include <bitset>

int main(int argc, char **argv)
{

    auto desc = Description::CPU(PATH);
    desc.generate();

    // Intel4004 cpu;

    // bitset a{{0xFF,0xFF,0xFF}, 20};
    // for (int i = 0; i < 10; i++)
    // {
    //     std::cout << (a >> i).show() << "\n";
    // }

    //     bitset b{{0b10111}, 5};
    // for (int i = 0; i < 5; i++)
    // {
    //     std::cout << (b >> i).show() << "\n";
    // }
    // for (int i = 0; i < 255; i++)
    // {
    //     auto g = get(&cpu.memory[0], ACC) + bitset({1},4);
    //     set(&cpu.memory[0], ACC, g);
    // }


    // std::cout << get(&cpu.memory[0], ACC).show() << "\n";

    // auto n = YAML::Load("3");
    // Description::Memory m("hi", n);
    // m.size = 14;
    // m.offset = 0;

    // for (const auto a : m.getBitmask())
    // {
    //     std::cout << std::bitset<8>(a) << '\n';
    // }
    return 0;
}
