#include <iostream>
#include "yaml-cpp/yaml.h"
#include "../include/description.hpp"

#define PATH "test_files/intel4004.yaml"

int main(int argc, char** argv)
{
    auto desc = Description::CPU(PATH);

    return 0;
}
