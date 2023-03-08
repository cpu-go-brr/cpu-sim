#include "Intel4004.hpp"

#include <fstream>
int main(int argc, char **argv)
{
    Intel4004 cpu;

    for(int i = 0; i < 92592; i++)
    {
        cpu.iac<0b11110010>();
    }
    return 0;
}
