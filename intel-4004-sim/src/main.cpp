#include <iostream>
#include "../include/intel4004.hpp"


int main(int argc, char** argv)
{

    Intel4004 cpu;

    cpu.set_object_code({0xAB,0xCD,0xEF});
    cpu.print_status();
    cpu.simultate();
    cpu.print_status();


    return 0;
}