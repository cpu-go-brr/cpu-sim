#include <iostream>
#include "../include/intel4004.hpp"


int main(int argc, char** argv)
{

    Intel4004 cpu;

    cpu.set_object_code({0x20,0xA2,0xA0,0x81,0xB1,0x40,0x05});
    cpu.print_status();
    //return 0;

    for(int i = 0; i < 6; i++)
    {
        cpu.simultate();
        cpu.print_status();
    }

    return 0;
}