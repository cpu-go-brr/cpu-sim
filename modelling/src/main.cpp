#include <iostream>
#include "yaml-cpp/yaml.h"
#include "../include/description.hpp"
#include "../include/matheval.hpp"

#define PATH "test_files/intel4004.yaml"

#include <bitset>

int main(int argc, char **argv)
{

    // auto n = YAML::Load("3");
    // Description::Memory m("hi", n);
    // m.size = 14;
    // m.offset = 0;

    // for (const auto a : m.getBitmask())
    // {
    //     std::cout << std::bitset<8>(a) << '\n';
    // }
    auto desc = Description::CPU(PATH);

    return 0;
}
