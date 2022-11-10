#include <iostream>
#include <iomanip>
#include "cpu.hpp"
#include "matheval.hpp"
#include "bitset.hpp"
#include "assembler.hpp"

#define PATH "test_files/intel4004.yaml"

#include <bitset>

void test_generic_assembler();

int main(int argc, char **argv)
{
    test_generic_assembler();
    // bitset a{{0b1010}, 4};
    // bitset b{{1}, 1};

    // std::cout << (a,b).bin() << "\n";

    // auto desc = Description::CPU(PATH);
    // desc.generate();
// 
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

void test_generic_assembler(){
    GenercicAssembler gasm = GenercicAssembler();
    std::vector<int> assembled_code = gasm.assemble("test_files/input.asm", "test_files/intel4004.yaml");

    std::cout << "\n\nAssembled Code:\n";
    for (size_t i = 0; i < assembled_code.size(); i++)
    {
        std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << assembled_code[i] << " ";
    }
    std::cout << "\n\n\n";
}