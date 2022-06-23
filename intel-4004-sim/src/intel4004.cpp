#include "../include/intel4004.hpp"
#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>

void Intel4004::simultate()
{
    std::cout << "I'm simulating..\n";
    unsigned int instr = code[pc] & 0xF;
    int instr_index = 0;
    std::cout << "searching for: " << std::bitset<32>(instr) << "\n";
    while(!ops.contains(instr))
    {
        instr_index++;
        
        //std::cout << "shift 4 left:\n";
        //instr = (instr << 4);
        //std::cout << std::bitset<32>(instr) << "\n";
        
        std::cout << "index:" << ((float)pc + ((float)instr_index / (float)2)) << "\n";
        std::cout << "new part:" << std::hex << ((int)(code[pc + (instr_index / 2)]) & (instr_index % 2)?0xF:0xF0) << "\n";

        //instr = (instr << 4) + ((code[pc + (instr_index / 2)] & (instr_index % 2)?0xF:0xF0) >> (instr_index % 2?0:4));
        std::cout << "not found :(\nsearching for: " << std::bitset<32>(instr) << "\n";

        if(instr_index > 4)
        {
            std::cout << "No fitting OP-Code found\n";
            return;
        }
    }
    


}


void Intel4004::print_status()
{
    std::cout << "PC: " << std::to_string(pc) << "\n";
}



void Intel4004::set_object_code(std::vector<uint8_t> c)
{
    code = c;
}
