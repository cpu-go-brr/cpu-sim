#include <iostream>
#include "../include/intel4004.hpp"
#include "../include/parsing.hpp"

void test_parsing();
void test_cpu();

int main(int argc, char** argv){

    // test_cpu();
    test_parsing();

    return 0;
}

void test_cpu(){
    Intel4004 cpu;

    cpu.set_object_code({0x20,0xA2,0xA0,0x81,0xB1,0x40,0x05});
    cpu.print_status();
    //return 0;

    for(int i = 0; i < 6; i++)
    {
        cpu.simultate();
        cpu.print_status();
    }
}

void test_parsing(){
    Intel4004Parser parser;
    parser.parse("input2.asm");
}