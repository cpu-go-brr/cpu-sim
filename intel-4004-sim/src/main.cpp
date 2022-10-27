#include <iostream>
#include "../include/intel4004.hpp"
#include "../include/assembler/intel4004_assembler.hpp"
#include "../include/server.hpp"

void test_parsing();
void test_cpu();

int main(int argc, char** argv)
{
    // Intel4004 cpu;

    // auto server = Server(2001, &cpu);
    // server.start();

    // test_cpu();
    test_parsing();

    return 0;
}

void test_cpu(){
    Intel4004 cpu;

    cpu.set_object_code({0x50, 0x08, 0x50, 0x0F, 0x40, 0x02, 0x40, 0x0D,
0x2C, 0x37, 0x2E, 0x11, 0xC0, 0x40, 0x0D, 0xAC,
0xB0, 0xAD, 0xB1, 0xAD, 0xF4, 0x1C, 0x1B, 0xD0,
0xF1, 0x9E, 0xBE, 0xAD, 0x1C, 0x22, 0xD0, 0xF1,
0x9E, 0xBE, 0xAC, 0x1C, 0x29, 0xD0, 0xF1, 0x9F,
0xBF, 0xD8, 0xB2, 0xAC, 0x92, 0xF4, 0x1C, 0x34,
0xD0, 0xF1, 0x9F, 0xBF, 0xAD, 0xF1, 0x8E, 0xBD,
0xAC, 0xF1, 0x8F, 0xBC, 0x21, 0xD0, 0xE0, 0x2D,
0xD1, 0xE0, 0xC0
});
    // cpu.print_status();
    //return 0;

    for(int i = 0;true; i++)
    {
        cpu.simultate();
        cpu.print_status();
    }
}

#include <iomanip>
#include <vector>
void test_parsing(){
    Intel4004Assembler assembler;
    std::vector<int> assembled_code = assembler.assemble("input.asm");

    std::cout << "\n\nAssembled Code:\n";
    for (size_t i = 0; i < assembled_code.size(); i++)
    {
        std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << assembled_code[i] << " ";
    }
    std::cout << "\n\n\n";
}