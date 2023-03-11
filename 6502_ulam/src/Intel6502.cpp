#include "Intel6502.hpp"
#include <stdio.h>
#include <stdlib.h>
/* */
template <>
void Intel6502::adc_immediate<0b01101001>()
{
/* AC + mem(PC+1) + CF --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set((get(AC)+mem(get(PC)+1)+get(CF)), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::adc_zeropage<0b01100101>()
{
/* AC + mem(mem(PC+1)) + CF --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set((get(AC)+mem(mem(get(PC)+1))+get(CF)), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::adc_zeropage_x<0b01110101>()
{
/* AC + mem(mem(PC+1)+XX) + CF --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set((get(AC)+mem(mem(get(PC)+1)+get(XX))+get(CF)), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::adc_absolute<0b01101101>()
{
/* AC + mem((mem(PC+1),mem(PC+2))) + CF --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set((get(AC)+mem((mem(get(PC)+1),mem(get(PC)+2)))+get(CF)), 2,__addr_infos);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::adc_absolute_x<0b01111101>()
{
/* AC + ((mem(PC+2),mem(PC+1))+XX) + CF --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set((get(AC)+((mem(get(PC)+2),mem(get(PC)+1))+get(XX))+get(CF)), 2,__addr_infos);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::adc_absolute_y<0b01111001>()
{
/* AC + ((mem(PC+2),mem(PC+1))+YY) + CF --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set((get(AC)+((mem(get(PC)+2),mem(get(PC)+1))+get(YY))+get(CF)), 2,__addr_infos);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::adc_indirect_x<0b01100001>()
{
/* AC + (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+XX) + CF --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set((get(AC)+(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(XX))+get(CF)), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::adc_indirect_y<0b01110001>()
{
/* AC + (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+YY) + CF --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set((get(AC)+(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(YY))+get(CF)), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::and_immediate<0b00101001>()
{
/* (AC & mem(PC+1)) --> AC*/
set(((get(AC)&mem(get(PC)+1))), AC);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::and_zeropage<0b00100101>()
{
/* (AC & mem(mem(PC+1))) --> AC*/
set(((get(AC)&mem(mem(get(PC)+1)))), AC);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::and_zeropage_x<0b00110101>()
{
/* (AC & mem(mem(PC+1)+XX)) --> AC*/
set(((get(AC)&mem(mem(get(PC)+1)+get(XX)))), AC);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::and_absolute<0b00101101>()
{
/* (AC & (mem(PC+2),mem(PC+1))) --> AC*/
set(((get(AC)&(mem(get(PC)+2),mem(get(PC)+1)))), AC);
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::and_absolute_x<0b00111101>()
{
/* (AC & ((mem(PC+2),mem(PC+1))+XX)) --> AC*/
set(((get(AC)&((mem(get(PC)+2),mem(get(PC)+1))+get(XX)))), AC);
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::and_absolute_y<0b00111001>()
{
/* (AC & ((mem(PC+2),mem(PC+1))+YY)) --> AC*/
set(((get(AC)&((mem(get(PC)+2),mem(get(PC)+1))+get(YY)))), AC);
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::and_indirect_x<0b00100001>()
{
/* (AC & (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+XX)) --> AC*/
set(((get(AC)&(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(XX)))), AC);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::and_indirect_y<0b00110001>()
{
/* (AC & (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+YY)) --> AC*/
set(((get(AC)&(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(YY)))), AC);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::asl_accumulator<0b00001010>()
{
/* (AC,0) --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set(((get(AC),0)), 2,__addr_infos);
}
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::asl_zeropage<0b00000110>()
{
/* (mem(mem(PC+1)),0) --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set(((mem(mem(get(PC)+1)),0)), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::asl_zeropage_x<0b00010110>()
{
/* (mem(mem(PC+1)+XX),0) --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set(((mem(mem(get(PC)+1)+get(XX)),0)), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::asl_absolute<0b00001110>()
{
/* ((mem(PC+2),mem(PC+1)),0) --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set((((mem(get(PC)+2),mem(get(PC)+1)),0)), 2,__addr_infos);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::asl_absolute_x<0b00011110>()
{
/* (((mem(PC+2),mem(PC+1))+XX),0) --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set(((((mem(get(PC)+2),mem(get(PC)+1))+get(XX)),0)), 2,__addr_infos);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::bcc_relative<0b10010000>()
{
/* (CF == 0) ? PC+mem(PC+1) --> PC*/
if((get(CF)==0))
{
set((get(PC)+mem(get(PC)+1)), PC);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}


/* */
template <>
void Intel6502::bcs_relative<0b10110000>()
{
/* (CF == 1) ? PC+mem(PC+1) --> PC*/
if((get(CF)==1))
{
set((get(PC)+mem(get(PC)+1)), PC);
}
}


/* */
template <>
void Intel6502::beq_relative<0b11110000>()
{
/* (ZF == 1) ? PC+mem(PC+1) --> PC*/
if((get(ZF)==1))
{
set((get(PC)+mem(get(PC)+1)), PC);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}


/* */
template <>
void Intel6502::bmi_relative<0b00110000>()
{
/* (NF == 1) ? PC+mem(PC+1)+(-128) --> PC*/
if((get(NF)==1))
{
set((get(PC)+mem(get(PC)+1)+(-128)), PC);
}
}


/* */
template <>
void Intel6502::bne_relative<0b11010000>()
{
/* (ZF == 0) ? PC+mem(PC+1)+(-128) --> PC*/
if((get(ZF)==0))
{
set((get(PC)+mem(get(PC)+1)+(-128)), PC);
}
}


/* */
template <>
void Intel6502::bpl_relative<0b00010000>()
{
/* (NF == 0) ? PC+mem(PC+1)+(-128) --> PC*/
if((get(NF)==0))
{
set((get(PC)+mem(get(PC)+1)+(-128)), PC);
}
}


/* */
template <>
void Intel6502::bvc_relative<0b01010000>()
{
/* (VF == 0) ? PC+mem(PC+1)+(-128) --> PC*/
if((get(VF)==0))
{
set((get(PC)+mem(get(PC)+1)+(-128)), PC);
}
}


/* */
template <>
void Intel6502::bvs_relative<0b01110000>()
{
/* (VF == 1) ? PC+mem(PC+1)+(-128) --> PC*/
if((get(VF)==1))
{
set((get(PC)+mem(get(PC)+1)+(-128)), PC);
}
}


/* */
template <>
void Intel6502::clc_implied<0b00011000>()
{
/* 0 --> CF*/
set((0), CF);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* */
template <>
void Intel6502::cld_implied<0b11011000>()
{
/* 0 --> DF*/
set((0), DF);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* */
template <>
void Intel6502::cli_implied<0b01011000>()
{
/* 0 --> IF*/
set((0), IF);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* */
template <>
void Intel6502::clv_implied<0b10111000>()
{
/* 0 --> VF*/
set((0), VF);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* */
template <>
void Intel6502::cmp_immediate<0b11001001>()
{
/* (AC < mem(PC+1)) ? 0 --> ZF*/
if((get(AC)<mem(get(PC)+1)))
{
set((0), ZF);
}
/* (AC < mem(PC+1)) ? 0 --> CF*/
if((get(AC)<mem(get(PC)+1)))
{
set((0), CF);
}
/* (AC < mem(PC+1)) --> NF*/
set(((get(AC)<mem(get(PC)+1))), NF);
/* (AC == mem(PC+1)) ? 1 --> ZF*/
if((get(AC)==mem(get(PC)+1)))
{
set((1), ZF);
}
/* (AC == mem(PC+1)) ? 1 --> CF*/
if((get(AC)==mem(get(PC)+1)))
{
set((1), CF);
}
/* (AC == mem(PC+1)) ? 0 --> NF*/
if((get(AC)==mem(get(PC)+1)))
{
set((0), NF);
}
/* (AC > mem(PC+1)) ? 0 --> ZF*/
if((get(AC)>mem(get(PC)+1)))
{
set((0), ZF);
}
/* (AC > mem(PC+1)) ? 1 --> CF*/
if((get(AC)>mem(get(PC)+1)))
{
set((1), CF);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}


/* */
template <>
void Intel6502::cmp_zeropage<0b11000101>()
{
/* AC < mem(mem(PC+1)) ? 0 --> ZF*/
if(get(AC)<mem(mem(get(PC)+1)))
{
set((0), ZF);
}
/* AC < mem(mem(PC+1)) ? 0 --> CF*/
if(get(AC)<mem(mem(get(PC)+1)))
{
set((0), CF);
}
/* AC < mem(mem(PC+1)) --> NF*/
set((get(AC)<mem(mem(get(PC)+1))), NF);
/* AC == mem(mem(PC+1)) ? 1 --> ZF*/
if(get(AC)==mem(mem(get(PC)+1)))
{
set((1), ZF);
}
/* AC == mem(mem(PC+1)) ? 1 --> CF*/
if(get(AC)==mem(mem(get(PC)+1)))
{
set((1), CF);
}
/* AC == mem(mem(PC+1)) ? 0 --> NF*/
if(get(AC)==mem(mem(get(PC)+1)))
{
set((0), NF);
}
/* AC > mem(mem(PC+1)) ? 0 --> ZF*/
if(get(AC)>mem(mem(get(PC)+1)))
{
set((0), ZF);
}
/* AC > mem(mem(PC+1)) ? 1 --> CF*/
if(get(AC)>mem(mem(get(PC)+1)))
{
set((1), CF);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::cmp_zeropage_x<0b11010101>()
{
/* AC < mem(mem(PC+1)+XX) ? 0 --> ZF*/
if(get(AC)<mem(mem(get(PC)+1)+get(XX)))
{
set((0), ZF);
}
/* AC < mem(mem(PC+1)+XX) ? 0 --> CF*/
if(get(AC)<mem(mem(get(PC)+1)+get(XX)))
{
set((0), CF);
}
/* AC < mem(mem(PC+1)+XX) --> NF*/
set((get(AC)<mem(mem(get(PC)+1)+get(XX))), NF);
/* AC == mem(mem(PC+1)+XX) ? 1 --> ZF*/
if(get(AC)==mem(mem(get(PC)+1)+get(XX)))
{
set((1), ZF);
}
/* AC == mem(mem(PC+1)+XX) ? 1 --> CF*/
if(get(AC)==mem(mem(get(PC)+1)+get(XX)))
{
set((1), CF);
}
/* AC == mem(mem(PC+1)+XX) ? 0 --> NF*/
if(get(AC)==mem(mem(get(PC)+1)+get(XX)))
{
set((0), NF);
}
/* AC > mem(mem(PC+1)+XX) ? 0 --> ZF*/
if(get(AC)>mem(mem(get(PC)+1)+get(XX)))
{
set((0), ZF);
}
/* AC > mem(mem(PC+1)+XX) ? 1 --> CF*/
if(get(AC)>mem(mem(get(PC)+1)+get(XX)))
{
set((1), CF);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::cmp_absolute<0b11001101>()
{
/* AC < (mem(PC+2),mem(PC+1)) ? 0 --> ZF*/
if(get(AC)<(mem(get(PC)+2),mem(get(PC)+1)))
{
set((0), ZF);
}
/* AC < (mem(PC+2),mem(PC+1)) ? 0 --> CF*/
if(get(AC)<(mem(get(PC)+2),mem(get(PC)+1)))
{
set((0), CF);
}
/* AC < (mem(PC+2),mem(PC+1)) --> NF*/
set((get(AC)<(mem(get(PC)+2),mem(get(PC)+1))), NF);
/* AC == (mem(PC+2),mem(PC+1)) ? 1 --> ZF*/
if(get(AC)==(mem(get(PC)+2),mem(get(PC)+1)))
{
set((1), ZF);
}
/* AC == (mem(PC+2),mem(PC+1)) ? 1 --> CF*/
if(get(AC)==(mem(get(PC)+2),mem(get(PC)+1)))
{
set((1), CF);
}
/* AC == (mem(PC+2),mem(PC+1)) ? 0 --> NF*/
if(get(AC)==(mem(get(PC)+2),mem(get(PC)+1)))
{
set((0), NF);
}
/* AC > (mem(PC+2),mem(PC+1)) ? 0 --> ZF*/
if(get(AC)>(mem(get(PC)+2),mem(get(PC)+1)))
{
set((0), ZF);
}
/* AC > (mem(PC+2),mem(PC+1)) ? 1 --> CF*/
if(get(AC)>(mem(get(PC)+2),mem(get(PC)+1)))
{
set((1), CF);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::cmp_absolute_x<0b11011101>()
{
/* AC < (mem(PC+2),mem(PC+1)+XX) ? 0 --> ZF*/
if(get(AC)<(mem(get(PC)+2),mem(get(PC)+1)+get(XX)))
{
set((0), ZF);
}
/* AC < (mem(PC+2),mem(PC+1)+XX) ? 0 --> CF*/
if(get(AC)<(mem(get(PC)+2),mem(get(PC)+1)+get(XX)))
{
set((0), CF);
}
/* AC < (mem(PC+2),mem(PC+1)+XX) --> NF*/
set((get(AC)<(mem(get(PC)+2),mem(get(PC)+1)+get(XX))), NF);
/* AC == (mem(PC+2),mem(PC+1)+XX) ? 1 --> ZF*/
if(get(AC)==(mem(get(PC)+2),mem(get(PC)+1)+get(XX)))
{
set((1), ZF);
}
/* AC == (mem(PC+2),mem(PC+1)+XX) ? 1 --> CF*/
if(get(AC)==(mem(get(PC)+2),mem(get(PC)+1)+get(XX)))
{
set((1), CF);
}
/* AC == (mem(PC+2),mem(PC+1)+XX) ? 0 --> NF*/
if(get(AC)==(mem(get(PC)+2),mem(get(PC)+1)+get(XX)))
{
set((0), NF);
}
/* AC > (mem(PC+2),mem(PC+1)+XX) ? 0 --> ZF*/
if(get(AC)>(mem(get(PC)+2),mem(get(PC)+1)+get(XX)))
{
set((0), ZF);
}
/* AC > (mem(PC+2),mem(PC+1)+XX) ? 1 --> CF*/
if(get(AC)>(mem(get(PC)+2),mem(get(PC)+1)+get(XX)))
{
set((1), CF);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::cmp_absolute_y<0b11011001>()
{
/* AC < (mem(PC+2),mem(PC+1)+YY) ? 0 --> ZF*/
if(get(AC)<(mem(get(PC)+2),mem(get(PC)+1)+get(YY)))
{
set((0), ZF);
}
/* AC < (mem(PC+2),mem(PC+1)+YY) ? 0 --> CF*/
if(get(AC)<(mem(get(PC)+2),mem(get(PC)+1)+get(YY)))
{
set((0), CF);
}
/* AC < (mem(PC+2),mem(PC+1)+YY) --> NF*/
set((get(AC)<(mem(get(PC)+2),mem(get(PC)+1)+get(YY))), NF);
/* AC == (mem(PC+2),mem(PC+1)+YY) ? 1 --> ZF*/
if(get(AC)==(mem(get(PC)+2),mem(get(PC)+1)+get(YY)))
{
set((1), ZF);
}
/* AC == (mem(PC+2),mem(PC+1)+YY) ? 1 --> CF*/
if(get(AC)==(mem(get(PC)+2),mem(get(PC)+1)+get(YY)))
{
set((1), CF);
}
/* AC == (mem(PC+2),mem(PC+1)+YY) ? 0 --> NF*/
if(get(AC)==(mem(get(PC)+2),mem(get(PC)+1)+get(YY)))
{
set((0), NF);
}
/* AC > (mem(PC+2),mem(PC+1)+YY) ? 0 --> ZF*/
if(get(AC)>(mem(get(PC)+2),mem(get(PC)+1)+get(YY)))
{
set((0), ZF);
}
/* AC > (mem(PC+2),mem(PC+1)+YY) ? 1 --> CF*/
if(get(AC)>(mem(get(PC)+2),mem(get(PC)+1)+get(YY)))
{
set((1), CF);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::cmp_indirect_x<0b11000001>()
{
/* AC < (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+XX) ? 0 --> ZF*/
if(get(AC)<(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(XX)))
{
set((0), ZF);
}
/* AC < (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+XX) ? 0 --> CF*/
if(get(AC)<(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(XX)))
{
set((0), CF);
}
/* AC < (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+XX) --> NF*/
set((get(AC)<(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(XX))), NF);
/* AC == (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+XX) ? 1 --> ZF*/
if(get(AC)==(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(XX)))
{
set((1), ZF);
}
/* AC == (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+XX) ? 1 --> CF*/
if(get(AC)==(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(XX)))
{
set((1), CF);
}
/* AC == (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+XX) ? 0 --> NF*/
if(get(AC)==(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(XX)))
{
set((0), NF);
}
/* AC > (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+XX) ? 0 --> ZF*/
if(get(AC)>(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(XX)))
{
set((0), ZF);
}
/* AC > (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+XX) ? 1 --> CF*/
if(get(AC)>(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(XX)))
{
set((1), CF);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::cmp_indirect_y<0b11010001>()
{
/* AC < (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+YY) ? 0 --> ZF*/
if(get(AC)<(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(YY)))
{
set((0), ZF);
}
/* AC < (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+YY) ? 0 --> CF*/
if(get(AC)<(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(YY)))
{
set((0), CF);
}
/* AC < (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+YY) --> NF*/
set((get(AC)<(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(YY))), NF);
/* AC == (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+YY) ? 1 --> ZF*/
if(get(AC)==(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(YY)))
{
set((1), ZF);
}
/* AC == (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+YY) ? 1 --> CF*/
if(get(AC)==(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(YY)))
{
set((1), CF);
}
/* AC == (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+YY) ? 0 --> NF*/
if(get(AC)==(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(YY)))
{
set((0), NF);
}
/* AC > (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+YY) ? 0 --> ZF*/
if(get(AC)>(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(YY)))
{
set((0), ZF);
}
/* AC > (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+YY) ? 1 --> CF*/
if(get(AC)>(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(YY)))
{
set((1), CF);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::inx_implied<0b11101000>()
{
/* XX + 1 --> XX*/
set((get(XX)+1), XX);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* */
template <>
void Intel6502::jmp_absolute<0b1001100>()
{
/* mem(PC + 1), mem(PC + 2) --> PC*/
set((mem(get(PC)+1),mem(get(PC)+2)), PC);
}


/* */
template <>
void Intel6502::lda_immediate<0b10101001>()
{
/* mem(PC+1) --> AC*/
set((mem(get(PC)+1)), AC);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}


/* */
template <>
void Intel6502::lda_absolute<0b10101101>()
{
/* mem(PC+2),mem(PC+1) --> AC*/
set((mem(get(PC)+2),mem(get(PC)+1)), AC);
/* PC+3 --> PC*/
set((get(PC)+3), PC);
}


/* */
template <>
void Intel6502::lsr_accumulator<0b01001010>()
{
/* (0,AC) --> AC, CF*/
{
const AddressInfo __addr_infos[2] = {AC,CF};
set(((0,get(AC))), 2,__addr_infos);
}
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::lsr_zeropage<0b01000110>()
{
/* (0,mem(mem(PC+1))) --> AC, CF*/
{
const AddressInfo __addr_infos[2] = {AC,CF};
set(((0,mem(mem(get(PC)+1)))), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::lsr_zeropage_x<0b01010110>()
{
/* (0,mem(mem(PC+1)+XX)) --> AC, CF*/
{
const AddressInfo __addr_infos[2] = {AC,CF};
set(((0,mem(mem(get(PC)+1)+get(XX)))), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::lsr_absolute<0b01001110>()
{
/* (0,(mem(PC+2),mem(PC+1))) --> AC, CF*/
{
const AddressInfo __addr_infos[2] = {AC,CF};
set(((0,(mem(get(PC)+2),mem(get(PC)+1)))), 2,__addr_infos);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::lsr_absolute_x<0b01011110>()
{
/* (0,((mem(PC+2),mem(PC+1))+XX)) --> AC, CF*/
{
const AddressInfo __addr_infos[2] = {AC,CF};
set(((0,((mem(get(PC)+2),mem(get(PC)+1))+get(XX)))), 2,__addr_infos);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ora_immediate<0b00001001>()
{
/* AC | mem(PC+1) --> AC*/
set((get(AC)|mem(get(PC)+1)), AC);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ora_zeropage<0b00000101>()
{
/* AC | mem(mem(PC+1)) --> AC*/
set((get(AC)|mem(mem(get(PC)+1))), AC);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ora_zeropage_x<0b00010101>()
{
/* AC | mem(mem(PC+1)+XX) --> AC*/
set((get(AC)|mem(mem(get(PC)+1)+get(XX))), AC);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ora_absolute<0b00001101>()
{
/* AC | (mem(PC+2),mem(PC+1)) --> AC*/
set((get(AC)|(mem(get(PC)+2),mem(get(PC)+1))), AC);
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ora_absolute_x<0b00011101>()
{
/* AC | ((mem(PC+2),mem(PC+1))+XX) --> AC*/
set((get(AC)|((mem(get(PC)+2),mem(get(PC)+1))+get(XX))), AC);
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ora_absolute_y<0b00011001>()
{
/* AC | (mem(mem(PC+2)+YY),mem(mem(PC+1)+YY)) --> AC*/
set((get(AC)|(mem(mem(get(PC)+2)+get(YY)),mem(mem(get(PC)+1)+get(YY)))), AC);
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ora_indirect_x<0b00000001>()
{
/* AC | (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+XX) --> AC*/
set((get(AC)|(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(XX))), AC);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ora_indirect_y<0b00010001>()
{
/* AC | (mem(mem(mem(PC+2))),mem(mem(mem(PC+1)))+YY) --> AC*/
set((get(AC)|(mem(mem(mem(get(PC)+2))),mem(mem(mem(get(PC)+1)))+get(YY))), AC);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::rol_accumulator<0b00101010>()
{
/* (AC,CF) --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set(((get(AC),get(CF))), 2,__addr_infos);
}
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::rol_zeropage<0b00100110>()
{
/* (mem(mem(PC+1)),CF) --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set(((mem(mem(get(PC)+1)),get(CF))), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::rol_zeropage_x<0b00110110>()
{
/* (mem(mem(PC+1)+XX),CF) --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set(((mem(mem(get(PC)+1)+get(XX)),get(CF))), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::rol_absolute<0b00101110>()
{
/* ((mem(PC+2),mem(PC+1)),CF) --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set((((mem(get(PC)+2),mem(get(PC)+1)),get(CF))), 2,__addr_infos);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::rol_absolute_x<0b00111110>()
{
/* (((mem(PC+2),mem(PC+1))+XX),CF) --> CF, AC*/
{
const AddressInfo __addr_infos[2] = {CF,AC};
set(((((mem(get(PC)+2),mem(get(PC)+1))+get(XX)),get(CF))), 2,__addr_infos);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC & 128) > 0 --> NF*/
set(((get(AC)&128)>0), NF);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ror_accumulator<0b01101010>()
{
/* (CF,AC) --> AC, CF*/
{
const AddressInfo __addr_infos[2] = {AC,CF};
set(((get(CF),get(AC))), 2,__addr_infos);
}
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ror_zeropage<0b01100110>()
{
/* (CF,mem(mem(PC+1))) --> AC, CF*/
{
const AddressInfo __addr_infos[2] = {AC,CF};
set(((get(CF),mem(mem(get(PC)+1)))), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ror_zeropage_x<0b01110110>()
{
/* (CF,mem(mem(PC+1)+XX)) --> AC, CF*/
{
const AddressInfo __addr_infos[2] = {AC,CF};
set(((get(CF),mem(mem(get(PC)+1)+get(XX)))), 2,__addr_infos);
}
/* PC+2 --> PC*/
set((get(PC)+2), PC);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ror_absolute<0b01101110>()
{
/* (CF,(mem(PC+2),mem(PC+1))) --> AC, CF*/
{
const AddressInfo __addr_infos[2] = {AC,CF};
set(((get(CF),(mem(get(PC)+2),mem(get(PC)+1)))), 2,__addr_infos);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::ror_absolute_x<0b01111110>()
{
/* (CF,((mem(PC+2),mem(PC+1))+XX)) --> AC, CF*/
{
const AddressInfo __addr_infos[2] = {AC,CF};
set(((get(CF),((mem(get(PC)+2),mem(get(PC)+1))+get(XX)))), 2,__addr_infos);
}
/* PC+3 --> PC*/
set((get(PC)+3), PC);
/* (AC == 0) --> ZF*/
set(((get(AC)==0)), ZF);
}


/* */
template <>
void Intel6502::sta_absolute<0b10001101>()
{
/* AC --> mem((mem(PC+1)), mem(PC+2))*/
set((get(AC)), mem(((mem(get(PC)+1)), mem(get(PC)+2))));
/* PC+3 --> PC*/
set((get(PC)+3), PC);
}


Intel6502::op Intel6502::ops[256] = {
NULL,
&Intel6502::ora_indirect_x<0b00000001>,
NULL,
NULL,
NULL,
&Intel6502::ora_zeropage<0b00000101>,
&Intel6502::asl_zeropage<0b00000110>,
NULL,
NULL,
&Intel6502::ora_immediate<0b00001001>,
&Intel6502::asl_accumulator<0b00001010>,
NULL,
NULL,
&Intel6502::ora_absolute<0b00001101>,
&Intel6502::asl_absolute<0b00001110>,
NULL,
&Intel6502::bpl_relative<0b00010000>,
&Intel6502::ora_indirect_y<0b00010001>,
NULL,
NULL,
NULL,
&Intel6502::ora_zeropage_x<0b00010101>,
&Intel6502::asl_zeropage_x<0b00010110>,
NULL,
&Intel6502::clc_implied<0b00011000>,
&Intel6502::ora_absolute_y<0b00011001>,
NULL,
NULL,
NULL,
&Intel6502::ora_absolute_x<0b00011101>,
&Intel6502::asl_absolute_x<0b00011110>,
NULL,
NULL,
&Intel6502::and_indirect_x<0b00100001>,
NULL,
NULL,
NULL,
&Intel6502::and_zeropage<0b00100101>,
&Intel6502::rol_zeropage<0b00100110>,
NULL,
NULL,
&Intel6502::and_immediate<0b00101001>,
&Intel6502::rol_accumulator<0b00101010>,
NULL,
NULL,
&Intel6502::and_absolute<0b00101101>,
&Intel6502::rol_absolute<0b00101110>,
NULL,
&Intel6502::bmi_relative<0b00110000>,
&Intel6502::and_indirect_y<0b00110001>,
NULL,
NULL,
NULL,
&Intel6502::and_zeropage_x<0b00110101>,
&Intel6502::rol_zeropage_x<0b00110110>,
NULL,
NULL,
&Intel6502::and_absolute_y<0b00111001>,
NULL,
NULL,
NULL,
&Intel6502::and_absolute_x<0b00111101>,
&Intel6502::rol_absolute_x<0b00111110>,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
&Intel6502::lsr_zeropage<0b01000110>,
NULL,
NULL,
NULL,
&Intel6502::lsr_accumulator<0b01001010>,
NULL,
&Intel6502::jmp_absolute<0b1001100>,
NULL,
&Intel6502::lsr_absolute<0b01001110>,
NULL,
&Intel6502::bvc_relative<0b01010000>,
NULL,
NULL,
NULL,
NULL,
NULL,
&Intel6502::lsr_zeropage_x<0b01010110>,
NULL,
&Intel6502::cli_implied<0b01011000>,
NULL,
NULL,
NULL,
NULL,
NULL,
&Intel6502::lsr_absolute_x<0b01011110>,
NULL,
NULL,
&Intel6502::adc_indirect_x<0b01100001>,
NULL,
NULL,
NULL,
&Intel6502::adc_zeropage<0b01100101>,
&Intel6502::ror_zeropage<0b01100110>,
NULL,
NULL,
&Intel6502::adc_immediate<0b01101001>,
&Intel6502::ror_accumulator<0b01101010>,
NULL,
NULL,
&Intel6502::adc_absolute<0b01101101>,
&Intel6502::ror_absolute<0b01101110>,
NULL,
&Intel6502::bvs_relative<0b01110000>,
&Intel6502::adc_indirect_y<0b01110001>,
NULL,
NULL,
NULL,
&Intel6502::adc_zeropage_x<0b01110101>,
&Intel6502::ror_zeropage_x<0b01110110>,
NULL,
NULL,
&Intel6502::adc_absolute_y<0b01111001>,
NULL,
NULL,
NULL,
&Intel6502::adc_absolute_x<0b01111101>,
&Intel6502::ror_absolute_x<0b01111110>,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
&Intel6502::sta_absolute<0b10001101>,
NULL,
NULL,
&Intel6502::bcc_relative<0b10010000>,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
&Intel6502::lda_immediate<0b10101001>,
NULL,
NULL,
NULL,
&Intel6502::lda_absolute<0b10101101>,
NULL,
NULL,
&Intel6502::bcs_relative<0b10110000>,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
&Intel6502::clv_implied<0b10111000>,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
&Intel6502::cmp_indirect_x<0b11000001>,
NULL,
NULL,
NULL,
&Intel6502::cmp_zeropage<0b11000101>,
NULL,
NULL,
NULL,
&Intel6502::cmp_immediate<0b11001001>,
NULL,
NULL,
NULL,
&Intel6502::cmp_absolute<0b11001101>,
NULL,
NULL,
&Intel6502::bne_relative<0b11010000>,
&Intel6502::cmp_indirect_y<0b11010001>,
NULL,
NULL,
NULL,
&Intel6502::cmp_zeropage_x<0b11010101>,
NULL,
NULL,
&Intel6502::cld_implied<0b11011000>,
&Intel6502::cmp_absolute_y<0b11011001>,
NULL,
NULL,
NULL,
&Intel6502::cmp_absolute_x<0b11011101>,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
&Intel6502::inx_implied<0b11101000>,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
&Intel6502::beq_relative<0b11110000>,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL};
Intel6502::Intel6502()
{
for(auto i = 0ul; i < 65536; i ++)
mem_mem[i] = bitset(0,8);
for(auto i = 0ul; i < 2048; i ++)
ram_mem[i] = bitset(0,4);

}
void Intel6502::bin(AddressInfo info, char* addr)
{
       get(info).bin(addr);
    }
void Intel6502::hex(AddressInfo info, char* addr)
{
       get(info).hex(addr);
    }
void Intel6502::dec(AddressInfo info, char* addr)
{
       get(info).dec(addr);
    }
char* Intel6502::display()
{
if(str == NULL)
{
str = (char*)malloc(111);
sprintf(str, "     PC       AC        XX        YY        SP        NV-BDIZC\n\
     XXXX   XX    XX    XX    XX    XXXXXXXX\n\n\
");
}
hex(PC, str +68);
hex(AC, str +75);
hex(XX, str +81);
hex(YY, str +87);
hex(SP, str +93);
hex(NF, str +99);
hex(VF, str +100);
hex(IGF, str +101);
hex(BF, str +102);
hex(DF, str +103);
hex(IF, str +104);
hex(ZF, str +105);
hex(CF, str +106);
#ifndef NO_PRINT
printf("%s",str);
#endif
return str;
}
void Intel6502::simulate(size_t i)
{
for (;i-->0;)
{
   auto val = fetch();
   std::cout << "inst: " <<  std::hex << val.val() << "\n";
   if(ops[val.val()] == NULL)
   {
   #ifndef NO_PRINT
   fprintf(stderr, "%zx unknown\n", val.val());
   #endif
   break;
   }
   (this->*ops[val.val()])();
}
}
bitset& Intel6502::mem(AddressInfo info)
{
return mem(get(info));
}

bitset& Intel6502::mem(bitset index)
{
return mem_mem[index.val()];
}
#ifndef NO_CPPSTD
void Intel6502::flash_mem(std::vector<bitset> data)
{
for(auto i = 0ul; i < data.size(); i++)
mem_mem[i] = bitset(data[i], 8);
}

#endif
void Intel6502::flash_mem(bitset* data, size_t len)
{
for(auto i = 0ul; i < len; i++)
mem_mem[i] = bitset(data[i], 8);
}

bitset& Intel6502::ram(AddressInfo info)
{
return ram(get(info));
}

bitset& Intel6502::ram(bitset index)
{
return ram_mem[index.val()];
}
#ifndef NO_CPPSTD
void Intel6502::flash_ram(std::vector<bitset> data)
{
for(auto i = 0ul; i < data.size(); i++)
ram_mem[i] = bitset(data[i], 4);
}

#endif
void Intel6502::flash_ram(bitset* data, size_t len)
{
for(auto i = 0ul; i < len; i++)
ram_mem[i] = bitset(data[i], 4);
}

bitset Intel6502::fetch()
{
/* mem(PC)*/
return mem(get(PC));
}
void Intel6502::set(bitset data, AddressInfo info)
{
set_mem(&memory[0], info, data);
}
void Intel6502::set(bitset data, bitset& dest)
{
dest=bitset(data,dest.size());
}
void Intel6502::set(bitset data, int num, const AddressInfo* infos)
{
for(size_t i = num; i --> 0;)
{
set_mem(&memory[0], infos[i], data);
data = data >> infos[i].length;
}
}
bitset Intel6502::get(AddressInfo info)
{
   return get_mem(&memory[0], info);
}
#ifndef NO_CPPSTD
    std::string Intel6502::json()
{
std::string json = "{\"internal\":{"
"\"PC\":{\"bits\":16,\"val\":" + std::to_string(get(PC).val()) + "},"
"\"AC\":{\"bits\":8,\"val\":" + std::to_string(get(AC).val()) + "},"
"\"XX\":{\"bits\":8,\"val\":" + std::to_string(get(XX).val()) + "},"
"\"YY\":{\"bits\":8,\"val\":" + std::to_string(get(YY).val()) + "},"
"\"SR\":{"
"\"NF\":{\"bits\":1,\"val\":" + std::to_string(get(NF).val()) + "},"
"\"VF\":{\"bits\":1,\"val\":" + std::to_string(get(VF).val()) + "},"
"\"IGF\":{\"bits\":1,\"val\":" + std::to_string(get(IGF).val()) + "},"
"\"BF\":{\"bits\":1,\"val\":" + std::to_string(get(BF).val()) + "},"
"\"DF\":{\"bits\":1,\"val\":" + std::to_string(get(DF).val()) + "},"
"\"IF\":{\"bits\":1,\"val\":" + std::to_string(get(IF).val()) + "},"
"\"ZF\":{\"bits\":1,\"val\":" + std::to_string(get(ZF).val()) + "},"
"\"CF\":{\"bits\":1,\"val\":" + std::to_string(get(CF).val()) + "}"
"},"
"\"SP\":{\"bits\":8,\"val\":" + std::to_string(get(SP).val()) + "}},\"external\":{"
"\"mem\":{\"bits\":8,\"vals\":[";
for(size_t i = 0; i < 65536; i++) json += std::to_string(mem_mem[i].val()) + ",";
json = json.substr(0,json.size()-1);
json += "]},";
json +="\"ram\":{\"bits\":4,\"vals\":[";
for(size_t i = 0; i < 2048; i++) json += std::to_string(ram_mem[i].val()) + ",";
json = json.substr(0,json.size()-1);
json += "]"
"}}";
return json + "}";
}
#endif
