#include "../include/intel4004.hpp"

void Intel4004::nop()
{
    pc++;
}

void Intel4004::jun()
{
    pc = ((read_rom(pc) & 0xF) << 8) +read_rom(pc+1);
}

void Intel4004::ldm()
{
    acc = read_rom(pc) & 0xF;
    pc++;
}

void Intel4004::ld()
{
    acc = registers[read_rom(pc) & 0xF];
    pc++;
}

void Intel4004::xch()
{
    uint8_t acbr = acc;
    acc = registers[read_rom(pc) & 0xF];
    registers[read_rom(pc) & 0xF] = acbr;
    pc++;
}

void Intel4004::add()
{

    uint8_t addition = acc + registers[read_rom(pc) & 0xF] + carry;
    acc = addition & 0xF;
    carry = (addition & (1 << 4)) > 0;
    pc++;
}

void Intel4004::sub()
{
    uint8_t subtraction = acc + (~registers[read_rom(pc) & 0xF] & 0xF) + carry;
    acc = subtraction & 0xF;
    carry = (subtraction & (1 << 4)) > 0;
    pc++;
}


void Intel4004::fim()
{

    uint8_t r = read_rom(pc) & 0b1110;
    registers[r] = (read_rom(pc+1) & 0xF0) >> 4;
    registers[r+1] = read_rom(pc+1) & 0xF;
    pc+=2;
}


void Intel4004::inc()
{
    uint8_t r = read_rom(pc) & 0xF;
    registers[r] = (registers[r] +1) & 0xF;
    pc++;
}

void Intel4004::bbl(){return;}

void Intel4004::jin(){return;}
void Intel4004::src(){return;}
void Intel4004::fin(){return;}
void Intel4004::jms(){return;}
void Intel4004::jcn(){return;}
void Intel4004::isz(){return;}
void Intel4004::rdm(){return;}
void Intel4004::rd0(){return;}
void Intel4004::rd1(){return;}
void Intel4004::rd2(){return;}
void Intel4004::rd3(){return;}
void Intel4004::rdr(){return;}
void Intel4004::wrm(){return;}
void Intel4004::wr0(){return;}
void Intel4004::wr1(){return;}
void Intel4004::wr2(){return;}
void Intel4004::wr3(){return;}
void Intel4004::wrr(){return;}
void Intel4004::wmp(){return;}
void Intel4004::adm(){return;}
void Intel4004::sbm(){return;}
void Intel4004::clb(){return;}
void Intel4004::clc(){return;}
void Intel4004::cmc(){return;}
void Intel4004::stc(){return;}
void Intel4004::cma(){return;}
void Intel4004::iac(){return;}
void Intel4004::dac(){return;}
void Intel4004::ral(){return;}
void Intel4004::rar(){return;}
void Intel4004::tcc(){return;}
void Intel4004::daa(){return;}
void Intel4004::tcs(){return;}
void Intel4004::kbp(){return;}
void Intel4004::dcl(){return;}