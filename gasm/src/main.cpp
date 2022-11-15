#include <iostream>
#include <iomanip>
#include "gasm.hpp"

void test_general_assembler();

int main(int argc, char **argv)
{
    test_general_assembler();
    return 0;
}

void test_general_assembler(){
    GeneralAssembler gasm = GeneralAssembler();
    std::vector<int> assembled_code = gasm.assemble("input/input.asm", "input/intel4004.yaml");

    std::cout << "\n\nAssembled Code:\n";
    for (size_t i = 0; i < assembled_code.size(); i++)
    {
        std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << assembled_code[i] << " ";
    }
    std::cout << "\n\n\n";
}