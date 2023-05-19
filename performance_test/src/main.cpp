#include "Intel4004.hpp"

int main(int argc, char **argv)
{
    Intel4004 cpu;

    for(int i = 0; i < 100'000'000; i++)
    {
        cpu.iac<0b11110010>();
    }
    return 0;
}
