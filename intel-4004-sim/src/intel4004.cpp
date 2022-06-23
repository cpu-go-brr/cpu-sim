#include "../include/intel4004.hpp"
#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>

void Intel4004::simultate()
{
    //std::cout << "I'm simulating..\n";
    unsigned int instr = (code[pc] & 0xF0) >> 4;
    int instr_index = 0;
    std::cout << "searching for: " << std::hex << instr << "\n";
    while(!ops.contains(instr))
    {
        instr_index++;
        
        //read byte, mask high or low, shift if high was masked
        instr = (instr << 4) + ((((int)(code[pc + (instr_index / 2)])) & ((instr_index%2)?0xF:0xF0)) >> ((instr_index%2)?0:4));
        
        //std::cout << "not found :(\nsearching for: " << std::hex << instr << "\n";

        if(instr_index > 4)
        {
            std::cerr << "No fitting OP-Code found\n";
            return;
        }
    }
    (*this.*ops[instr])();


}


void Intel4004::print_status()
{
    std::cout << "PC: " << std::to_string(pc) << "\n";
}



void Intel4004::set_object_code(std::vector<uint8_t> c)
{
    code = c;
}
