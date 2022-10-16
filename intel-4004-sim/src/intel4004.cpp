#include "../include/intel4004.hpp"
#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>

uint8_t Intel4004::read_rom(unsigned int pos)
{
    if (pos >= code.size())
        return 0;
    return code[pos];
}

void Intel4004::simultate()
{
    // std::cout << "I'm simulating..\n";
    unsigned int instr = (read_rom(pc) & 0xF0) >> 4;
    int instr_index = 0;
    // std::cout << "code["<< pc << "] = " <<  instr << "\n";
    while (!ops.contains(instr))
    {
        instr_index++;

        // read byte, mask high or low, shift if high was masked
        instr = (instr << 4) + ((((int)(read_rom(pc))) & ((instr_index % 2) ? 0xF : 0xF0)) >> ((instr_index % 2) ? 0 : 4));

        if (instr_index > 4)
        {
            std::cerr << "No fitting OP-Code found\n";
            return;
        }
    }
    // std::cout << "fetched " << instr << "\n";
    (*this.*ops[instr])();
}

std::string u_int16_to_string(uint16_t t)
{
    std::stringstream ss;
    ss << std::hex << ((t & 0xF00) >> 8) << " " << ((t & 0xF0) >> 4) << " " << (t & 0xF);
    return ss.str();
}

std::string u_int8_to_string(uint8_t t)
{
    std::stringstream ss;
    ss << std::hex << (int)t;
    return ss.str();
}

std::string Intel4004::get_status()
{
    std::stringstream ss;

    ss << "        STACK                REGISTERS\n";
    ss << "     PC " << u_int16_to_string(pc) << "          R0 R1 " << u_int8_to_string(registers[0]) << " " << u_int8_to_string(registers[1]) << "  R8 R9 " << u_int8_to_string(registers[8]) << " " << u_int8_to_string(registers[9]) << "\n";
    ss << "LEVEL 1 " << u_int16_to_string(sr[0]) << "          R2 R3 " << u_int8_to_string(registers[2]) << " " << u_int8_to_string(registers[3]) << "  RA RB " << u_int8_to_string(registers[0xA]) << " " << u_int8_to_string(registers[0xB]) << "\n";
    ss << "LEVEL 2 " << u_int16_to_string(sr[1]) << "          R4 R5 " << u_int8_to_string(registers[4]) << " " << u_int8_to_string(registers[5]) << "  RC RD " << u_int8_to_string(registers[0xC]) << " " << u_int8_to_string(registers[0xD]) << "\n";
    ss << "LEVEL 3 " << u_int16_to_string(sr[2]) << "          R6 R7 " << u_int8_to_string(registers[6]) << " " << u_int8_to_string(registers[7]) << "  RE RF " << u_int8_to_string(registers[0xE]) << " " << u_int8_to_string(registers[0xF]) << "\n";
    ss << "\n";
    ss << "ACCUMULATOR: " << u_int8_to_string(acc) << " [" << std::bitset<4>(acc) << "]  CARRY: " << (carry ? "y" : "n") << " TEST: " << (test ? "y" : "n") << "\n";

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 16; x++)
            ss << std::hex << (0xF & ram[0].mem[y][x]);
        ss << std::endl;
    }

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 16; x++)
            ss << std::hex << (0xF & ram[1].mem[y][x]);
        ss << std::endl;
    }

    return ss.str();

}

void Intel4004::print_status()
{
    std::cout << get_status();
}

void Intel4004::set_object_code(std::vector<uint8_t> c)
{
    code = c;
}
