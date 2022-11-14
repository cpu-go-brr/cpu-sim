#include "Intel4004.hpp"
#include <stddef.h>
#include <stdio.h>
bitset Intel4004::get(AddressInfo info)
{
   return get_mem(&memory[0], info);
}
/* No Operation*/
template <>
void Intel4004::nop<0b00000000>()
{
/* PC + 1 --> PC*/
set((get(PC)+1), PC);
}


/* If the designated condition code is true, program control is transferred to the instruction 
located at the 8 bit address A2A2A2A2, A1A1A1A1 on the same page (ROM) where JCN is located.
If the condition is not true the next instruction in sequence after JCN is executed.
The condition bits are assigned as follows:
I = 0 Do not invert jump condition
I = 1 Invert jump condition
Z = 1 Jump if the accumulator content is zero
O = 1 Jump if the carry/link content is 1
T = 1 Jump if test signal (pin 10 on 4004) is zero.
*/
template <>
void Intel4004::jcn<0b00010000>()
{
[[maybe_unused]] bitset I{0b0, 1};
[[maybe_unused]] bitset O{0b0, 1};
[[maybe_unused]] bitset T{0b0, 1};
[[maybe_unused]] bitset Z{0b0, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00010001>()
{
[[maybe_unused]] bitset I{0b0, 1};
[[maybe_unused]] bitset O{0b0, 1};
[[maybe_unused]] bitset T{0b1, 1};
[[maybe_unused]] bitset Z{0b0, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00010010>()
{
[[maybe_unused]] bitset I{0b0, 1};
[[maybe_unused]] bitset O{0b1, 1};
[[maybe_unused]] bitset T{0b0, 1};
[[maybe_unused]] bitset Z{0b0, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00010011>()
{
[[maybe_unused]] bitset I{0b0, 1};
[[maybe_unused]] bitset O{0b1, 1};
[[maybe_unused]] bitset T{0b1, 1};
[[maybe_unused]] bitset Z{0b0, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00010100>()
{
[[maybe_unused]] bitset I{0b0, 1};
[[maybe_unused]] bitset O{0b0, 1};
[[maybe_unused]] bitset T{0b0, 1};
[[maybe_unused]] bitset Z{0b1, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00010101>()
{
[[maybe_unused]] bitset I{0b0, 1};
[[maybe_unused]] bitset O{0b0, 1};
[[maybe_unused]] bitset T{0b1, 1};
[[maybe_unused]] bitset Z{0b1, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00010110>()
{
[[maybe_unused]] bitset I{0b0, 1};
[[maybe_unused]] bitset O{0b1, 1};
[[maybe_unused]] bitset T{0b0, 1};
[[maybe_unused]] bitset Z{0b1, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00010111>()
{
[[maybe_unused]] bitset I{0b0, 1};
[[maybe_unused]] bitset O{0b1, 1};
[[maybe_unused]] bitset T{0b1, 1};
[[maybe_unused]] bitset Z{0b1, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00011000>()
{
[[maybe_unused]] bitset I{0b1, 1};
[[maybe_unused]] bitset O{0b0, 1};
[[maybe_unused]] bitset T{0b0, 1};
[[maybe_unused]] bitset Z{0b0, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00011001>()
{
[[maybe_unused]] bitset I{0b1, 1};
[[maybe_unused]] bitset O{0b0, 1};
[[maybe_unused]] bitset T{0b1, 1};
[[maybe_unused]] bitset Z{0b0, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00011010>()
{
[[maybe_unused]] bitset I{0b1, 1};
[[maybe_unused]] bitset O{0b1, 1};
[[maybe_unused]] bitset T{0b0, 1};
[[maybe_unused]] bitset Z{0b0, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00011011>()
{
[[maybe_unused]] bitset I{0b1, 1};
[[maybe_unused]] bitset O{0b1, 1};
[[maybe_unused]] bitset T{0b1, 1};
[[maybe_unused]] bitset Z{0b0, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00011100>()
{
[[maybe_unused]] bitset I{0b1, 1};
[[maybe_unused]] bitset O{0b0, 1};
[[maybe_unused]] bitset T{0b0, 1};
[[maybe_unused]] bitset Z{0b1, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00011101>()
{
[[maybe_unused]] bitset I{0b1, 1};
[[maybe_unused]] bitset O{0b0, 1};
[[maybe_unused]] bitset T{0b1, 1};
[[maybe_unused]] bitset Z{0b1, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00011110>()
{
[[maybe_unused]] bitset I{0b1, 1};
[[maybe_unused]] bitset O{0b1, 1};
[[maybe_unused]] bitset T{0b0, 1};
[[maybe_unused]] bitset Z{0b1, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}

template <>
void Intel4004::jcn<0b00011111>()
{
[[maybe_unused]] bitset I{0b1, 1};
[[maybe_unused]] bitset O{0b1, 1};
[[maybe_unused]] bitset T{0b1, 1};
[[maybe_unused]] bitset Z{0b1, 1};
bool zero=(bool)Z&&((bool)I^(get(ACC)==0));
bool carry=(bool)O&&((bool)I^(get(CY)==1));
bool test=(bool)T&&((bool)I^(get(TEST)==0));
bool jump=zero+carry+test;
bool nextpage=(get(PM),get(PL))>=254;
/* !jump? PC + 2 --> PC*/
if(!jump)
{
set((get(PC)+2), PC);
}
/* jump ? rom(PC+1) --> PM,PL*/
if(jump)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
/* jump && nextpage ? PH +1 --> PH*/
if(jump&&nextpage)
{
set((get(PH)+1), PH);
}
}


/* Load 8-bits of data which are loaded into the designated index register pair from ROM.
*/
template <>
void Intel4004::fim<0b00100000>()
{
[[maybe_unused]] bitset R{0b000, 3};
/* rom(PC+1) --> P{R}*/
set((rom(get(PC)+1)), P0);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}

template <>
void Intel4004::fim<0b00100010>()
{
[[maybe_unused]] bitset R{0b001, 3};
/* rom(PC+1) --> P{R}*/
set((rom(get(PC)+1)), P1);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}

template <>
void Intel4004::fim<0b00100100>()
{
[[maybe_unused]] bitset R{0b010, 3};
/* rom(PC+1) --> P{R}*/
set((rom(get(PC)+1)), P2);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}

template <>
void Intel4004::fim<0b00100110>()
{
[[maybe_unused]] bitset R{0b011, 3};
/* rom(PC+1) --> P{R}*/
set((rom(get(PC)+1)), P3);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}

template <>
void Intel4004::fim<0b00101000>()
{
[[maybe_unused]] bitset R{0b100, 3};
/* rom(PC+1) --> P{R}*/
set((rom(get(PC)+1)), P4);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}

template <>
void Intel4004::fim<0b00101010>()
{
[[maybe_unused]] bitset R{0b101, 3};
/* rom(PC+1) --> P{R}*/
set((rom(get(PC)+1)), P5);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}

template <>
void Intel4004::fim<0b00101100>()
{
[[maybe_unused]] bitset R{0b110, 3};
/* rom(PC+1) --> P{R}*/
set((rom(get(PC)+1)), P6);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}

template <>
void Intel4004::fim<0b00101110>()
{
[[maybe_unused]] bitset R{0b111, 3};
/* rom(PC+1) --> P{R}*/
set((rom(get(PC)+1)), P7);
/* PC+2 --> PC*/
set((get(PC)+2), PC);
}


/* The 8 bit content of the designated index register pair is sent to 
the RAM address register at X2 and X3. A subsequent read, write, 
or I/O operation of the RAM will utilize this address. Specifically, 
the first 2 bits of the address designatea RAM chip; the second 2 bits 
designate 1 out of 4 registers within the chip; the last 4 bits designate 
1 out of 16 4-bit main memory characters within the register. This command 
is also used to designate a ROM for a subsequent ROM I/O port operation. 
The first 4 bits designate the ROM chip number to be selected. The address 
in ROM or RAM is not cleared until the next SRC instruction is executed. 
The 8 bit content of the index register is unaffected.
*/
template <>
void Intel4004::src<0b00100001>()
{
[[maybe_unused]] bitset R{0b000, 3};
/* P{R} --> SRC*/
set((get(P0)), SRC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::src<0b00100011>()
{
[[maybe_unused]] bitset R{0b001, 3};
/* P{R} --> SRC*/
set((get(P1)), SRC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::src<0b00100101>()
{
[[maybe_unused]] bitset R{0b010, 3};
/* P{R} --> SRC*/
set((get(P2)), SRC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::src<0b00100111>()
{
[[maybe_unused]] bitset R{0b011, 3};
/* P{R} --> SRC*/
set((get(P3)), SRC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::src<0b00101001>()
{
[[maybe_unused]] bitset R{0b100, 3};
/* P{R} --> SRC*/
set((get(P4)), SRC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::src<0b00101011>()
{
[[maybe_unused]] bitset R{0b101, 3};
/* P{R} --> SRC*/
set((get(P5)), SRC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::src<0b00101101>()
{
[[maybe_unused]] bitset R{0b110, 3};
/* P{R} --> SRC*/
set((get(P6)), SRC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::src<0b00101111>()
{
[[maybe_unused]] bitset R{0b111, 3};
/* P{R} --> SRC*/
set((get(P7)), SRC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The 8 bit content of the 0 index register pair (0000) (0001) is sent out as 
an address in the same page where the FIN instruction is located. The 8 bit 
word at that location is loaded into the designated index register pair. 
The program counter is unaffected; after FIN has been executed the next 
instruction in sequence will be addressed. The content of the 0 index 
register pair is unaltered unless index register 0 was designated.
*/
template <>
void Intel4004::fin<0b00110000>()
{
[[maybe_unused]] bitset R{0b000, 3};
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* rom((PH, P0)) --> P{R}*/
set((rom((get(PH),get(P0)))), P0);
}

template <>
void Intel4004::fin<0b00110010>()
{
[[maybe_unused]] bitset R{0b001, 3};
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* rom((PH, P0)) --> P{R}*/
set((rom((get(PH),get(P0)))), P1);
}

template <>
void Intel4004::fin<0b00110100>()
{
[[maybe_unused]] bitset R{0b010, 3};
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* rom((PH, P0)) --> P{R}*/
set((rom((get(PH),get(P0)))), P2);
}

template <>
void Intel4004::fin<0b00110110>()
{
[[maybe_unused]] bitset R{0b011, 3};
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* rom((PH, P0)) --> P{R}*/
set((rom((get(PH),get(P0)))), P3);
}

template <>
void Intel4004::fin<0b00111000>()
{
[[maybe_unused]] bitset R{0b100, 3};
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* rom((PH, P0)) --> P{R}*/
set((rom((get(PH),get(P0)))), P4);
}

template <>
void Intel4004::fin<0b00111010>()
{
[[maybe_unused]] bitset R{0b101, 3};
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* rom((PH, P0)) --> P{R}*/
set((rom((get(PH),get(P0)))), P5);
}

template <>
void Intel4004::fin<0b00111100>()
{
[[maybe_unused]] bitset R{0b110, 3};
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* rom((PH, P0)) --> P{R}*/
set((rom((get(PH),get(P0)))), P6);
}

template <>
void Intel4004::fin<0b00111110>()
{
[[maybe_unused]] bitset R{0b111, 3};
/* PC+1 --> PC*/
set((get(PC)+1), PC);
/* rom((PH, P0)) --> P{R}*/
set((rom((get(PH),get(P0)))), P7);
}


/* The 8 bit content of the designated index register pair is loaded 
into the low order 8 positions of the program counter. Program control 
is transferred to the instruction at that address on the same page (same ROM) 
where the JIN instruction is located. The 8 bit content of the index register is unaffected.
*/
template <>
void Intel4004::jin<0b00110001>()
{
[[maybe_unused]] bitset R{0b000, 3};
/* PC +1 --> PC*/
set((get(PC)+1), PC);
/* R{2*R} --> PM*/
set((get(R0)), PM);
/* R{2*R+1} --> PL*/
set((get(R1)), PL);
}

template <>
void Intel4004::jin<0b00110011>()
{
[[maybe_unused]] bitset R{0b001, 3};
/* PC +1 --> PC*/
set((get(PC)+1), PC);
/* R{2*R} --> PM*/
set((get(R2)), PM);
/* R{2*R+1} --> PL*/
set((get(R3)), PL);
}

template <>
void Intel4004::jin<0b00110101>()
{
[[maybe_unused]] bitset R{0b010, 3};
/* PC +1 --> PC*/
set((get(PC)+1), PC);
/* R{2*R} --> PM*/
set((get(R4)), PM);
/* R{2*R+1} --> PL*/
set((get(R5)), PL);
}

template <>
void Intel4004::jin<0b00110111>()
{
[[maybe_unused]] bitset R{0b011, 3};
/* PC +1 --> PC*/
set((get(PC)+1), PC);
/* R{2*R} --> PM*/
set((get(R6)), PM);
/* R{2*R+1} --> PL*/
set((get(R7)), PL);
}

template <>
void Intel4004::jin<0b00111001>()
{
[[maybe_unused]] bitset R{0b100, 3};
/* PC +1 --> PC*/
set((get(PC)+1), PC);
/* R{2*R} --> PM*/
set((get(R8)), PM);
/* R{2*R+1} --> PL*/
set((get(R9)), PL);
}

template <>
void Intel4004::jin<0b00111011>()
{
[[maybe_unused]] bitset R{0b101, 3};
/* PC +1 --> PC*/
set((get(PC)+1), PC);
/* R{2*R} --> PM*/
set((get(R10)), PM);
/* R{2*R+1} --> PL*/
set((get(R11)), PL);
}

template <>
void Intel4004::jin<0b00111101>()
{
[[maybe_unused]] bitset R{0b110, 3};
/* PC +1 --> PC*/
set((get(PC)+1), PC);
/* R{2*R} --> PM*/
set((get(R12)), PM);
/* R{2*R+1} --> PL*/
set((get(R13)), PL);
}

template <>
void Intel4004::jin<0b00111111>()
{
[[maybe_unused]] bitset R{0b111, 3};
/* PC +1 --> PC*/
set((get(PC)+1), PC);
/* R{2*R} --> PM*/
set((get(R14)), PM);
/* R{2*R+1} --> PL*/
set((get(R15)), PL);
}


/* Jump unconditional*/
template <>
void Intel4004::jun<0b01000000>()
{
[[maybe_unused]] bitset A{0b0000, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01000001>()
{
[[maybe_unused]] bitset A{0b0001, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01000010>()
{
[[maybe_unused]] bitset A{0b0010, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01000011>()
{
[[maybe_unused]] bitset A{0b0011, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01000100>()
{
[[maybe_unused]] bitset A{0b0100, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01000101>()
{
[[maybe_unused]] bitset A{0b0101, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01000110>()
{
[[maybe_unused]] bitset A{0b0110, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01000111>()
{
[[maybe_unused]] bitset A{0b0111, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01001000>()
{
[[maybe_unused]] bitset A{0b1000, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01001001>()
{
[[maybe_unused]] bitset A{0b1001, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01001010>()
{
[[maybe_unused]] bitset A{0b1010, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01001011>()
{
[[maybe_unused]] bitset A{0b1011, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01001100>()
{
[[maybe_unused]] bitset A{0b1100, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01001101>()
{
[[maybe_unused]] bitset A{0b1101, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01001110>()
{
[[maybe_unused]] bitset A{0b1110, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jun<0b01001111>()
{
[[maybe_unused]] bitset A{0b1111, 4};
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}


/* The address of the next instruction in sequence following JMS (return address)
is saved in the push down stack. Program control is transferred to the instruction 
located at the 12 bit address (A3A3A3A3A2A2A2A2A1A1A1A1). Execution of a return 
instruction (BBL) will cause the saved address to be pulled out of the stack, 
therefore, program control is transferred to the next sequential instruction after 
the last JMS. The push down stack has 4 registers. One of them is used as the program 
counter, therefore nesting of JMS can occur up to 3 levels.
*/
template <>
void Intel4004::jms<0b01010000>()
{
[[maybe_unused]] bitset A{0b0000, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01010001>()
{
[[maybe_unused]] bitset A{0b0001, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01010010>()
{
[[maybe_unused]] bitset A{0b0010, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01010011>()
{
[[maybe_unused]] bitset A{0b0011, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01010100>()
{
[[maybe_unused]] bitset A{0b0100, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01010101>()
{
[[maybe_unused]] bitset A{0b0101, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01010110>()
{
[[maybe_unused]] bitset A{0b0110, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01010111>()
{
[[maybe_unused]] bitset A{0b0111, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01011000>()
{
[[maybe_unused]] bitset A{0b1000, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01011001>()
{
[[maybe_unused]] bitset A{0b1001, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01011010>()
{
[[maybe_unused]] bitset A{0b1010, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01011011>()
{
[[maybe_unused]] bitset A{0b1011, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01011100>()
{
[[maybe_unused]] bitset A{0b1100, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01011101>()
{
[[maybe_unused]] bitset A{0b1101, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01011110>()
{
[[maybe_unused]] bitset A{0b1110, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}

template <>
void Intel4004::jms<0b01011111>()
{
[[maybe_unused]] bitset A{0b1111, 4};
/* STACK1 --> STACK2*/
set((get(STACK1)), STACK2);
/* STACK0 --> STACK1*/
set((get(STACK0)), STACK1);
/* PC + 2 --> STACK0*/
set((get(PC)+2), STACK0);
/* (A, rom(PC+1))--> PC*/
set(((A,rom(get(PC)+1))), PC);
}


/* The 4 bit content of the designated index register is incremented by 1. 
The index register is set to zero in case of overflow. The carry/link is unaffected.
*/
template <>
void Intel4004::inc<0b01100000>()
{
[[maybe_unused]] bitset R{0b0000, 4};
/* R{R} + 1 --> R{R}*/
set((get(R0)+1), R0);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01100001>()
{
[[maybe_unused]] bitset R{0b0001, 4};
/* R{R} + 1 --> R{R}*/
set((get(R1)+1), R1);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01100010>()
{
[[maybe_unused]] bitset R{0b0010, 4};
/* R{R} + 1 --> R{R}*/
set((get(R2)+1), R2);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01100011>()
{
[[maybe_unused]] bitset R{0b0011, 4};
/* R{R} + 1 --> R{R}*/
set((get(R3)+1), R3);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01100100>()
{
[[maybe_unused]] bitset R{0b0100, 4};
/* R{R} + 1 --> R{R}*/
set((get(R4)+1), R4);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01100101>()
{
[[maybe_unused]] bitset R{0b0101, 4};
/* R{R} + 1 --> R{R}*/
set((get(R5)+1), R5);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01100110>()
{
[[maybe_unused]] bitset R{0b0110, 4};
/* R{R} + 1 --> R{R}*/
set((get(R6)+1), R6);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01100111>()
{
[[maybe_unused]] bitset R{0b0111, 4};
/* R{R} + 1 --> R{R}*/
set((get(R7)+1), R7);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01101000>()
{
[[maybe_unused]] bitset R{0b1000, 4};
/* R{R} + 1 --> R{R}*/
set((get(R8)+1), R8);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01101001>()
{
[[maybe_unused]] bitset R{0b1001, 4};
/* R{R} + 1 --> R{R}*/
set((get(R9)+1), R9);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01101010>()
{
[[maybe_unused]] bitset R{0b1010, 4};
/* R{R} + 1 --> R{R}*/
set((get(R10)+1), R10);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01101011>()
{
[[maybe_unused]] bitset R{0b1011, 4};
/* R{R} + 1 --> R{R}*/
set((get(R11)+1), R11);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01101100>()
{
[[maybe_unused]] bitset R{0b1100, 4};
/* R{R} + 1 --> R{R}*/
set((get(R12)+1), R12);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01101101>()
{
[[maybe_unused]] bitset R{0b1101, 4};
/* R{R} + 1 --> R{R}*/
set((get(R13)+1), R13);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01101110>()
{
[[maybe_unused]] bitset R{0b1110, 4};
/* R{R} + 1 --> R{R}*/
set((get(R14)+1), R14);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::inc<0b01101111>()
{
[[maybe_unused]] bitset R{0b1111, 4};
/* R{R} + 1 --> R{R}*/
set((get(R15)+1), R15);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the designated index register is incremented by 1. The accumulator and 
carry/link are unaffected. If the result is zero, the next instruction after ISZ is 
executed. If the result is different from 0, program control is transferred to the 
instruction located at the 8 bit address A2A2A2A2, A1A1A1A1 on the same page (ROM) 
where the ISZ instruction is located.
*/
template <>
void Intel4004::isz<0b01110000>()
{
[[maybe_unused]] bitset R{0b0000, 4};
/* R{R} + 1 --> R{R}*/
set((get(R0)+1), R0);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R0)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R0)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01110001>()
{
[[maybe_unused]] bitset R{0b0001, 4};
/* R{R} + 1 --> R{R}*/
set((get(R1)+1), R1);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R1)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R1)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01110010>()
{
[[maybe_unused]] bitset R{0b0010, 4};
/* R{R} + 1 --> R{R}*/
set((get(R2)+1), R2);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R2)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R2)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01110011>()
{
[[maybe_unused]] bitset R{0b0011, 4};
/* R{R} + 1 --> R{R}*/
set((get(R3)+1), R3);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R3)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R3)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01110100>()
{
[[maybe_unused]] bitset R{0b0100, 4};
/* R{R} + 1 --> R{R}*/
set((get(R4)+1), R4);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R4)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R4)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01110101>()
{
[[maybe_unused]] bitset R{0b0101, 4};
/* R{R} + 1 --> R{R}*/
set((get(R5)+1), R5);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R5)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R5)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01110110>()
{
[[maybe_unused]] bitset R{0b0110, 4};
/* R{R} + 1 --> R{R}*/
set((get(R6)+1), R6);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R6)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R6)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01110111>()
{
[[maybe_unused]] bitset R{0b0111, 4};
/* R{R} + 1 --> R{R}*/
set((get(R7)+1), R7);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R7)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R7)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01111000>()
{
[[maybe_unused]] bitset R{0b1000, 4};
/* R{R} + 1 --> R{R}*/
set((get(R8)+1), R8);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R8)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R8)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01111001>()
{
[[maybe_unused]] bitset R{0b1001, 4};
/* R{R} + 1 --> R{R}*/
set((get(R9)+1), R9);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R9)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R9)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01111010>()
{
[[maybe_unused]] bitset R{0b1010, 4};
/* R{R} + 1 --> R{R}*/
set((get(R10)+1), R10);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R10)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R10)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01111011>()
{
[[maybe_unused]] bitset R{0b1011, 4};
/* R{R} + 1 --> R{R}*/
set((get(R11)+1), R11);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R11)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R11)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01111100>()
{
[[maybe_unused]] bitset R{0b1100, 4};
/* R{R} + 1 --> R{R}*/
set((get(R12)+1), R12);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R12)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R12)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01111101>()
{
[[maybe_unused]] bitset R{0b1101, 4};
/* R{R} + 1 --> R{R}*/
set((get(R13)+1), R13);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R13)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R13)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01111110>()
{
[[maybe_unused]] bitset R{0b1110, 4};
/* R{R} + 1 --> R{R}*/
set((get(R14)+1), R14);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R14)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R14)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}

template <>
void Intel4004::isz<0b01111111>()
{
[[maybe_unused]] bitset R{0b1111, 4};
/* R{R} + 1 --> R{R}*/
set((get(R15)+1), R15);
/* R{R} == 0 ? PC +2 --> PC*/
if(get(R15)==0)
{
set((get(PC)+2), PC);
}
/* R{R} != 0 ? rom(PC+1) --> PM,PL*/
if(get(R15)!=0)
{
set((rom(get(PC)+1)), 2,PL,PM);
}
}


/* The 4 bit content of the designated index register is added to the content of the 
accumulator with carry. The result is stored in the accumulator. The carry/link is 
set to 1 if a sum greater than 15 was generated to indicate a carry out; otherwise, 
the carry/link is set to 0. The 4 bit content of the index register is unaffected.
*/
template <>
void Intel4004::add<0b10000000>()
{
[[maybe_unused]] bitset R{0b0000, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R0)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10000001>()
{
[[maybe_unused]] bitset R{0b0001, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R1)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10000010>()
{
[[maybe_unused]] bitset R{0b0010, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R2)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10000011>()
{
[[maybe_unused]] bitset R{0b0011, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R3)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10000100>()
{
[[maybe_unused]] bitset R{0b0100, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R4)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10000101>()
{
[[maybe_unused]] bitset R{0b0101, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R5)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10000110>()
{
[[maybe_unused]] bitset R{0b0110, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R6)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10000111>()
{
[[maybe_unused]] bitset R{0b0111, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R7)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10001000>()
{
[[maybe_unused]] bitset R{0b1000, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R8)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10001001>()
{
[[maybe_unused]] bitset R{0b1001, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R9)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10001010>()
{
[[maybe_unused]] bitset R{0b1010, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R10)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10001011>()
{
[[maybe_unused]] bitset R{0b1011, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R11)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10001100>()
{
[[maybe_unused]] bitset R{0b1100, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R12)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10001101>()
{
[[maybe_unused]] bitset R{0b1101, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R13)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10001110>()
{
[[maybe_unused]] bitset R{0b1110, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R14)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::add<0b10001111>()
{
[[maybe_unused]] bitset R{0b1111, 4};
/* R{R} + ACC + CY --> CY,ACC*/
set((get(R15)+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The 4 bit content of the designated index register is complemented (ones complement) 
and added to content of the accumulator with borrow and the result is stored in the 
accumulator. If a borrow is generated, the carry bit is set to 0; otherwise, it is 
set to 1. The 4 bit content of the index register is unaffected.
*/
template <>
void Intel4004::sub<0b10010000>()
{
[[maybe_unused]] bitset R{0b0000, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R0)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10010001>()
{
[[maybe_unused]] bitset R{0b0001, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R1)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10010010>()
{
[[maybe_unused]] bitset R{0b0010, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R2)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10010011>()
{
[[maybe_unused]] bitset R{0b0011, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R3)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10010100>()
{
[[maybe_unused]] bitset R{0b0100, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R4)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10010101>()
{
[[maybe_unused]] bitset R{0b0101, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R5)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10010110>()
{
[[maybe_unused]] bitset R{0b0110, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R6)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10010111>()
{
[[maybe_unused]] bitset R{0b0111, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R7)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10011000>()
{
[[maybe_unused]] bitset R{0b1000, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R8)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10011001>()
{
[[maybe_unused]] bitset R{0b1001, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R9)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10011010>()
{
[[maybe_unused]] bitset R{0b1010, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R10)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10011011>()
{
[[maybe_unused]] bitset R{0b1011, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R11)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10011100>()
{
[[maybe_unused]] bitset R{0b1100, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R12)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10011101>()
{
[[maybe_unused]] bitset R{0b1101, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R13)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10011110>()
{
[[maybe_unused]] bitset R{0b1110, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R14)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::sub<0b10011111>()
{
[[maybe_unused]] bitset R{0b1111, 4};
/* (~R{R} + ACC + ~CY) --> CY,ACC*/
set(((~get(R15)+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The 4 bit content of the designated index register (RRRR) is loaded into 
accumulator. The previous contents of the accumulator are lost. The 4 bit 
content of the index register and the carry/link bit are unaffected.
*/
template <>
void Intel4004::ld<0b10100000>()
{
[[maybe_unused]] bitset R{0b0000, 4};
/* R{R} --> ACC*/
set((get(R0)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10100001>()
{
[[maybe_unused]] bitset R{0b0001, 4};
/* R{R} --> ACC*/
set((get(R1)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10100010>()
{
[[maybe_unused]] bitset R{0b0010, 4};
/* R{R} --> ACC*/
set((get(R2)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10100011>()
{
[[maybe_unused]] bitset R{0b0011, 4};
/* R{R} --> ACC*/
set((get(R3)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10100100>()
{
[[maybe_unused]] bitset R{0b0100, 4};
/* R{R} --> ACC*/
set((get(R4)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10100101>()
{
[[maybe_unused]] bitset R{0b0101, 4};
/* R{R} --> ACC*/
set((get(R5)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10100110>()
{
[[maybe_unused]] bitset R{0b0110, 4};
/* R{R} --> ACC*/
set((get(R6)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10100111>()
{
[[maybe_unused]] bitset R{0b0111, 4};
/* R{R} --> ACC*/
set((get(R7)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10101000>()
{
[[maybe_unused]] bitset R{0b1000, 4};
/* R{R} --> ACC*/
set((get(R8)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10101001>()
{
[[maybe_unused]] bitset R{0b1001, 4};
/* R{R} --> ACC*/
set((get(R9)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10101010>()
{
[[maybe_unused]] bitset R{0b1010, 4};
/* R{R} --> ACC*/
set((get(R10)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10101011>()
{
[[maybe_unused]] bitset R{0b1011, 4};
/* R{R} --> ACC*/
set((get(R11)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10101100>()
{
[[maybe_unused]] bitset R{0b1100, 4};
/* R{R} --> ACC*/
set((get(R12)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10101101>()
{
[[maybe_unused]] bitset R{0b1101, 4};
/* R{R} --> ACC*/
set((get(R13)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10101110>()
{
[[maybe_unused]] bitset R{0b1110, 4};
/* R{R} --> ACC*/
set((get(R14)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ld<0b10101111>()
{
[[maybe_unused]] bitset R{0b1111, 4};
/* R{R} --> ACC*/
set((get(R15)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The 4 bit content of designated index register is loaded into the accumulator. 
The prior content of the accumulator is loaded into the designed register. 
The carry/link bit is unaffected.
*/
template <>
void Intel4004::xch<0b10110000>()
{
[[maybe_unused]] bitset R{0b0000, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R0))), 2,ACC,R0);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10110001>()
{
[[maybe_unused]] bitset R{0b0001, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R1))), 2,ACC,R1);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10110010>()
{
[[maybe_unused]] bitset R{0b0010, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R2))), 2,ACC,R2);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10110011>()
{
[[maybe_unused]] bitset R{0b0011, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R3))), 2,ACC,R3);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10110100>()
{
[[maybe_unused]] bitset R{0b0100, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R4))), 2,ACC,R4);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10110101>()
{
[[maybe_unused]] bitset R{0b0101, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R5))), 2,ACC,R5);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10110110>()
{
[[maybe_unused]] bitset R{0b0110, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R6))), 2,ACC,R6);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10110111>()
{
[[maybe_unused]] bitset R{0b0111, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R7))), 2,ACC,R7);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10111000>()
{
[[maybe_unused]] bitset R{0b1000, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R8))), 2,ACC,R8);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10111001>()
{
[[maybe_unused]] bitset R{0b1001, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R9))), 2,ACC,R9);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10111010>()
{
[[maybe_unused]] bitset R{0b1010, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R10))), 2,ACC,R10);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10111011>()
{
[[maybe_unused]] bitset R{0b1011, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R11))), 2,ACC,R11);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10111100>()
{
[[maybe_unused]] bitset R{0b1100, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R12))), 2,ACC,R12);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10111101>()
{
[[maybe_unused]] bitset R{0b1101, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R13))), 2,ACC,R13);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10111110>()
{
[[maybe_unused]] bitset R{0b1110, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R14))), 2,ACC,R14);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::xch<0b10111111>()
{
[[maybe_unused]] bitset R{0b1111, 4};
/* (ACC, R{R}) --> R{R}, ACC*/
set(((get(ACC),get(R15))), 2,ACC,R15);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The program counter (address stack) is pushed down one level. Program control 
transfers to the next instruction following the last jump to subroutine (JMS) 
instruction. The 4 bits of data DDDD stored in the OPA portion of the instruction 
are loaded to the accumulator.

BBL is used to return from subroutine to main program.
*/
template <>
void Intel4004::bbl<0b11000000>()
{
[[maybe_unused]] bitset D{0b0000, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11000001>()
{
[[maybe_unused]] bitset D{0b0001, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11000010>()
{
[[maybe_unused]] bitset D{0b0010, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11000011>()
{
[[maybe_unused]] bitset D{0b0011, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11000100>()
{
[[maybe_unused]] bitset D{0b0100, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11000101>()
{
[[maybe_unused]] bitset D{0b0101, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11000110>()
{
[[maybe_unused]] bitset D{0b0110, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11000111>()
{
[[maybe_unused]] bitset D{0b0111, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11001000>()
{
[[maybe_unused]] bitset D{0b1000, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11001001>()
{
[[maybe_unused]] bitset D{0b1001, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11001010>()
{
[[maybe_unused]] bitset D{0b1010, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11001011>()
{
[[maybe_unused]] bitset D{0b1011, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11001100>()
{
[[maybe_unused]] bitset D{0b1100, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11001101>()
{
[[maybe_unused]] bitset D{0b1101, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11001110>()
{
[[maybe_unused]] bitset D{0b1110, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}

template <>
void Intel4004::bbl<0b11001111>()
{
[[maybe_unused]] bitset D{0b1111, 4};
/* D --> ACC*/
set((D), ACC);
/* STACK0 --> PC*/
set((get(STACK0)), PC);
/* STACK1 --> STACK0*/
set((get(STACK1)), STACK0);
/* STACK2 --> STACK1*/
set((get(STACK2)), STACK1);
/* 0 --> STACK2*/
set((0), STACK2);
}


/* The 4 bits of data, DDDD stored in the OPA field of instruction
word are loaded into the accumulator. The previous contents of the
accumulator are lost. The carry/link bit is unaffected.
*/
template <>
void Intel4004::ldm<0b11010000>()
{
[[maybe_unused]] bitset D{0b0000, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11010001>()
{
[[maybe_unused]] bitset D{0b0001, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11010010>()
{
[[maybe_unused]] bitset D{0b0010, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11010011>()
{
[[maybe_unused]] bitset D{0b0011, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11010100>()
{
[[maybe_unused]] bitset D{0b0100, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11010101>()
{
[[maybe_unused]] bitset D{0b0101, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11010110>()
{
[[maybe_unused]] bitset D{0b0110, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11010111>()
{
[[maybe_unused]] bitset D{0b0111, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11011000>()
{
[[maybe_unused]] bitset D{0b1000, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11011001>()
{
[[maybe_unused]] bitset D{0b1001, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11011010>()
{
[[maybe_unused]] bitset D{0b1010, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11011011>()
{
[[maybe_unused]] bitset D{0b1011, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11011100>()
{
[[maybe_unused]] bitset D{0b1100, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11011101>()
{
[[maybe_unused]] bitset D{0b1101, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11011110>()
{
[[maybe_unused]] bitset D{0b1110, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}

template <>
void Intel4004::ldm<0b11011111>()
{
[[maybe_unused]] bitset D{0b1111, 4};
/* D --> ACC*/
set((D), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The accumulator content is written into the previously selected RAM 
main memory character location. The accumulator and carry/link are unaffected.
*/
template <>
void Intel4004::wrm<0b11100000>()
{
/* ACC --> ram((CM, SRC))*/
set((get(ACC)), ram((get(CM),SRC)));
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the accumulator is transferred to the RAM output port 
of the previously selected RAM chip. The data is available on the 
output pins until a new WMP is executed on the same RAM chip. The 
content of the ACC and the carry/link are unaramffected. 
(The LSB bit of the accumultor appears on O0, Pin 16, of the 4002.)
*/
template <>
void Intel4004::wmp<0b11100001>()
{
/* ACC --> ram_port(CM)*/
set((get(ACC)), ram_port(get(CM)));
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the accumulator is transferred to the ROM output port of 
the previously selected ROM chip. The data is available on the output 
pins until a new WRR is executed on the same chip. The ACC content and 
carry/link are unaffected. (The LSB bit of the accumulator appears on 
I/O0, pin 16, of the 4001). No operation is performed on I/O lines coded 
as inputs.    
*/
template <>
void Intel4004::wrr<0b11100010>()
{
/* ACC --> rom_port(X2)*/
set((get(ACC)), rom_port(get(X2)));
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the accumulator is written into the RAM status character 
0 of the previously selected RAM register. The accumulator and the carry/link 
are unaffected.
*/
template <>
void Intel4004::wr0<0b11100100>()
{
/* ACC --> ram_status((X2, 0b00))*/
set((get(ACC)), ram_status((get(X2),bitset(0,2))));
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the accumulator is written into the RAM status character 
1 of the previously selected RAM register. The accumulator and the carry/link 
are unaffected.
*/
template <>
void Intel4004::wr1<0b11100101>()
{
/* ACC --> ram_status((X2, 0b01))*/
set((get(ACC)), ram_status((get(X2),bitset(1,2))));
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the accumulator is written into the RAM status character 
2 of the previously selected RAM register. The accumulator and the carry/link 
are unaffected.
*/
template <>
void Intel4004::wr2<0b11100110>()
{
/* ACC --> ram_status((X2, 0b10))*/
set((get(ACC)), ram_status((get(X2),bitset(2,2))));
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the accumulator is written into the RAM status character 
3 of the previously selected RAM register. The accumulator and the carry/link 
are unaffected.
*/
template <>
void Intel4004::wr3<0b11100111>()
{
/* ACC --> ram_status((X2, 0b11))*/
set((get(ACC)), ram_status((get(X2),bitset(3,2))));
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the previously selected RAM character is subtracted from the 
accumulator with borrow. The RAM character is unaffected.    
*/
template <>
void Intel4004::sbm<0b11101000>()
{
/* (~ram((CM, SRC)) + ACC + ~CY) --> CY,ACC*/
set(((~ram((get(CM),get(SRC)))+get(ACC)+~get(CY))), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the previously selected RAM main memory character is transferred 
to the accumulator. The carry/link is unaffected. The 4-bit data in memory is unaffected.
*/
template <>
void Intel4004::rdm<0b11101001>()
{
/* ram((CM, SRC)) --> ACC*/
set((ram((get(CM),get(SRC)))), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The data present at the input lines of the previously selected ROM chip is transferred to 
the accumulator. The carry/link is unaffected. If the I/O option has both inputs and outputs 
within the same 4 I/O lines, the user can choose to have either "0" or "1" transferred to the 
accumulator for those I/O pins coded as outputs, when an RDR instruction is executed.    
*/
template <>
void Intel4004::rdr<0b11101010>()
{
/* rom_port(X2) --> ACC*/
set((rom_port(get(X2))), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the previously selected RAM main memory character is added to the accumulator 
with carry. The RAM character is unaffected.
*/
template <>
void Intel4004::adm<0b11101011>()
{
/* ram((CM, SRC)) + ACC + CY --> CY,ACC*/
set((ram((get(CM),get(SRC)))+get(ACC)+get(CY)), 2,ACC,CY);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The 4-bits of status character 0 for the previously selected RAM register are transferred 
to the accumulator. The carry/link and the status character are unaffected.    
*/
template <>
void Intel4004::rd0<0b11101100>()
{
/* ram_status((X2, 0b00)) --> ACC*/
set((ram_status((get(X2),bitset(0,2)))), ACC);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The 4-bits of status character 1 for the previously selected RAM register are transferred 
to the accumulator. The carry/link and the status character are unaffected.    
*/
template <>
void Intel4004::rd1<0b11101101>()
{
/* ram_status((X2, 0b01)) --> ACC*/
set((ram_status((get(X2),bitset(1,2)))), ACC);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The 4-bits of status character 0 for the previously selected RAM register are transferred 
to the accumulator. The carry/link and the status character are unaffected.    
*/
template <>
void Intel4004::rd2<0b11101110>()
{
/* ram_status((X2, 0b10)) --> ACC*/
set((ram_status((get(X2),bitset(2,2)))), ACC);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* The 4-bits of status character 0 for the previously selected RAM register are transferred 
to the accumulator. The carry/link and the status character are unaffected.    
*/
template <>
void Intel4004::rd3<0b11101111>()
{
/* ram_status((X2, 0b11)) --> ACC*/
set((ram_status((get(X2),bitset(3,2)))), ACC);
/* PC +1 --> PC*/
set((get(PC)+1), PC);
}


/* Set accumulator and carry/link to 0.*/
template <>
void Intel4004::clb<0b11110000>()
{
/* 0 --> ACC*/
set((0), ACC);
/* 0 --> CY*/
set((0), CY);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* Clear Carry*/
template <>
void Intel4004::clc<0b11110001>()
{
/* 0 --> CY*/
set((0), CY);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* Complement Carry*/
template <>
void Intel4004::cmc<0b11110011>()
{
/* ~CY --> CY*/
set((~get(CY)), CY);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* Set Carry*/
template <>
void Intel4004::stc<0b11111010>()
{
/* 1 --> CY*/
set((1), CY);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* Complement Accumulator*/
template <>
void Intel4004::cma<0b11110100>()
{
/* ~ACC --> ACC*/
set((~get(ACC)), ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* Increment Accumulator*/
template <>
void Intel4004::iac<0b11110010>()
{
/* ACC+1 --> CY,ACC*/
set((get(ACC)+1), 2,ACC,CY);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* Decrement Accumulator*/
template <>
void Intel4004::dac<0b11111000>()
{
/* ACC+0b1111 --> CY,ACC*/
set((get(ACC)+0b1111), 2,ACC,CY);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the accumulator and carry/link are rotated left.
*/
template <>
void Intel4004::ral<0b11110110>()
{
/* (CY,ACC) --> ACC,CY*/
set(((get(CY),get(ACC))), 2,CY,ACC);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the accumulator and carry/link are rotated right.
*/
template <>
void Intel4004::rar<0b11110110>()
{
/* (ACC,CY) --> CY,ACC*/
set(((get(ACC),get(CY))), 2,ACC,CY);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The accumulator is cleared. The least significant position of 
the accumulator is set to the value of the carry/link.
The carry/link is set to 0.
*/
template <>
void Intel4004::tcc<0b11110111>()
{
/* 0 --> ACC*/
set((0), ACC);
/* CY --> ACC*/
set((get(CY)), ACC);
/* 0 --> CY*/
set((0), CY);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The accumulator is incremented by 6 if either the carry/link is 1 
or if the accumulator content is greater than 9.
The carry/link is set to a 1 if the result generates a carry, 
otherwise it is unaffected.
*/
template <>
void Intel4004::daa<0b11111011>()
{
bool inc=get(CY)==1||get(ACC)>9;
/* inc? ACC + 6 --> CY,ACC*/
if(inc)
{
set((get(ACC)+6), 2,ACC,CY);
}
}


/* The accumulator is set to 9 if the carry/link is 0.
The accumulator is set to 10 if the carry/link is a 1.
The carry/link is set to 0.
*/
template <>
void Intel4004::tcs<0b11111001>()
{
/* CY == 0 ? 0b1001 --> ACC*/
if(get(CY)==0)
{
set((0b1001), ACC);
}
/* CY == 1 ? 0b1010 --> ACC*/
if(get(CY)==1)
{
set((0b1010), ACC);
}
/* 0 --> CY*/
set((0), CY);
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The Accumulator will be set to the position of the first bit. If more than one bit is set the Accumulator will be set to 15*/
template <>
void Intel4004::kbp<0b11111100>()
{
bool keep=get(ACC)<3;
bool four=get(ACC)==4;
bool eight=get(ACC)==8;
bool error=!keep&&!four&&!eight;
/* four ? 3 --> ACC*/
if(four)
{
set((3), ACC);
}
/* eight ? 4 --> ACC*/
if(eight)
{
set((4), ACC);
}
/* error ? 15 --> ACC*/
if(error)
{
set((15), ACC);
}
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


/* The content of the three least significant accumulator bits is
transferred to the CM-RAM output lines on the cpu.
This instruction provides RAM bank selection when multiple RAM
banks are used. When the CPU is reset, RAM Bank zero is auto-
matically selected. DCL remains latched until it is changed or
reset.
*/
template <>
void Intel4004::dcl<0b11111101>()
{
/* ACC == 0 ? 1 --> CM*/
if(get(ACC)==0)
{
set((1), CM);
}
/* ACC != 0 ? (ACC, 0b0) --> CM*/
if(get(ACC)!=0)
{
set(((get(ACC),bitset(0,1))), CM);
}
/* PC+1 --> PC*/
set((get(PC)+1), PC);
}


Intel4004::op Intel4004::ops[256] = {
&Intel4004::nop<0b00000000>,
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
&Intel4004::jcn<0b00010000>,
&Intel4004::jcn<0b00010001>,
&Intel4004::jcn<0b00010010>,
&Intel4004::jcn<0b00010011>,
&Intel4004::jcn<0b00010100>,
&Intel4004::jcn<0b00010101>,
&Intel4004::jcn<0b00010110>,
&Intel4004::jcn<0b00010111>,
&Intel4004::jcn<0b00011000>,
&Intel4004::jcn<0b00011001>,
&Intel4004::jcn<0b00011010>,
&Intel4004::jcn<0b00011011>,
&Intel4004::jcn<0b00011100>,
&Intel4004::jcn<0b00011101>,
&Intel4004::jcn<0b00011110>,
&Intel4004::jcn<0b00011111>,
&Intel4004::fim<0b00100000>,
&Intel4004::src<0b00100001>,
&Intel4004::fim<0b00100010>,
&Intel4004::src<0b00100011>,
&Intel4004::fim<0b00100100>,
&Intel4004::src<0b00100101>,
&Intel4004::fim<0b00100110>,
&Intel4004::src<0b00100111>,
&Intel4004::fim<0b00101000>,
&Intel4004::src<0b00101001>,
&Intel4004::fim<0b00101010>,
&Intel4004::src<0b00101011>,
&Intel4004::fim<0b00101100>,
&Intel4004::src<0b00101101>,
&Intel4004::fim<0b00101110>,
&Intel4004::src<0b00101111>,
&Intel4004::fin<0b00110000>,
&Intel4004::jin<0b00110001>,
&Intel4004::fin<0b00110010>,
&Intel4004::jin<0b00110011>,
&Intel4004::fin<0b00110100>,
&Intel4004::jin<0b00110101>,
&Intel4004::fin<0b00110110>,
&Intel4004::jin<0b00110111>,
&Intel4004::fin<0b00111000>,
&Intel4004::jin<0b00111001>,
&Intel4004::fin<0b00111010>,
&Intel4004::jin<0b00111011>,
&Intel4004::fin<0b00111100>,
&Intel4004::jin<0b00111101>,
&Intel4004::fin<0b00111110>,
&Intel4004::jin<0b00111111>,
&Intel4004::jun<0b01000000>,
&Intel4004::jun<0b01000001>,
&Intel4004::jun<0b01000010>,
&Intel4004::jun<0b01000011>,
&Intel4004::jun<0b01000100>,
&Intel4004::jun<0b01000101>,
&Intel4004::jun<0b01000110>,
&Intel4004::jun<0b01000111>,
&Intel4004::jun<0b01001000>,
&Intel4004::jun<0b01001001>,
&Intel4004::jun<0b01001010>,
&Intel4004::jun<0b01001011>,
&Intel4004::jun<0b01001100>,
&Intel4004::jun<0b01001101>,
&Intel4004::jun<0b01001110>,
&Intel4004::jun<0b01001111>,
&Intel4004::jms<0b01010000>,
&Intel4004::jms<0b01010001>,
&Intel4004::jms<0b01010010>,
&Intel4004::jms<0b01010011>,
&Intel4004::jms<0b01010100>,
&Intel4004::jms<0b01010101>,
&Intel4004::jms<0b01010110>,
&Intel4004::jms<0b01010111>,
&Intel4004::jms<0b01011000>,
&Intel4004::jms<0b01011001>,
&Intel4004::jms<0b01011010>,
&Intel4004::jms<0b01011011>,
&Intel4004::jms<0b01011100>,
&Intel4004::jms<0b01011101>,
&Intel4004::jms<0b01011110>,
&Intel4004::jms<0b01011111>,
&Intel4004::inc<0b01100000>,
&Intel4004::inc<0b01100001>,
&Intel4004::inc<0b01100010>,
&Intel4004::inc<0b01100011>,
&Intel4004::inc<0b01100100>,
&Intel4004::inc<0b01100101>,
&Intel4004::inc<0b01100110>,
&Intel4004::inc<0b01100111>,
&Intel4004::inc<0b01101000>,
&Intel4004::inc<0b01101001>,
&Intel4004::inc<0b01101010>,
&Intel4004::inc<0b01101011>,
&Intel4004::inc<0b01101100>,
&Intel4004::inc<0b01101101>,
&Intel4004::inc<0b01101110>,
&Intel4004::inc<0b01101111>,
&Intel4004::isz<0b01110000>,
&Intel4004::isz<0b01110001>,
&Intel4004::isz<0b01110010>,
&Intel4004::isz<0b01110011>,
&Intel4004::isz<0b01110100>,
&Intel4004::isz<0b01110101>,
&Intel4004::isz<0b01110110>,
&Intel4004::isz<0b01110111>,
&Intel4004::isz<0b01111000>,
&Intel4004::isz<0b01111001>,
&Intel4004::isz<0b01111010>,
&Intel4004::isz<0b01111011>,
&Intel4004::isz<0b01111100>,
&Intel4004::isz<0b01111101>,
&Intel4004::isz<0b01111110>,
&Intel4004::isz<0b01111111>,
&Intel4004::add<0b10000000>,
&Intel4004::add<0b10000001>,
&Intel4004::add<0b10000010>,
&Intel4004::add<0b10000011>,
&Intel4004::add<0b10000100>,
&Intel4004::add<0b10000101>,
&Intel4004::add<0b10000110>,
&Intel4004::add<0b10000111>,
&Intel4004::add<0b10001000>,
&Intel4004::add<0b10001001>,
&Intel4004::add<0b10001010>,
&Intel4004::add<0b10001011>,
&Intel4004::add<0b10001100>,
&Intel4004::add<0b10001101>,
&Intel4004::add<0b10001110>,
&Intel4004::add<0b10001111>,
&Intel4004::sub<0b10010000>,
&Intel4004::sub<0b10010001>,
&Intel4004::sub<0b10010010>,
&Intel4004::sub<0b10010011>,
&Intel4004::sub<0b10010100>,
&Intel4004::sub<0b10010101>,
&Intel4004::sub<0b10010110>,
&Intel4004::sub<0b10010111>,
&Intel4004::sub<0b10011000>,
&Intel4004::sub<0b10011001>,
&Intel4004::sub<0b10011010>,
&Intel4004::sub<0b10011011>,
&Intel4004::sub<0b10011100>,
&Intel4004::sub<0b10011101>,
&Intel4004::sub<0b10011110>,
&Intel4004::sub<0b10011111>,
&Intel4004::ld<0b10100000>,
&Intel4004::ld<0b10100001>,
&Intel4004::ld<0b10100010>,
&Intel4004::ld<0b10100011>,
&Intel4004::ld<0b10100100>,
&Intel4004::ld<0b10100101>,
&Intel4004::ld<0b10100110>,
&Intel4004::ld<0b10100111>,
&Intel4004::ld<0b10101000>,
&Intel4004::ld<0b10101001>,
&Intel4004::ld<0b10101010>,
&Intel4004::ld<0b10101011>,
&Intel4004::ld<0b10101100>,
&Intel4004::ld<0b10101101>,
&Intel4004::ld<0b10101110>,
&Intel4004::ld<0b10101111>,
&Intel4004::xch<0b10110000>,
&Intel4004::xch<0b10110001>,
&Intel4004::xch<0b10110010>,
&Intel4004::xch<0b10110011>,
&Intel4004::xch<0b10110100>,
&Intel4004::xch<0b10110101>,
&Intel4004::xch<0b10110110>,
&Intel4004::xch<0b10110111>,
&Intel4004::xch<0b10111000>,
&Intel4004::xch<0b10111001>,
&Intel4004::xch<0b10111010>,
&Intel4004::xch<0b10111011>,
&Intel4004::xch<0b10111100>,
&Intel4004::xch<0b10111101>,
&Intel4004::xch<0b10111110>,
&Intel4004::xch<0b10111111>,
&Intel4004::bbl<0b11000000>,
&Intel4004::bbl<0b11000001>,
&Intel4004::bbl<0b11000010>,
&Intel4004::bbl<0b11000011>,
&Intel4004::bbl<0b11000100>,
&Intel4004::bbl<0b11000101>,
&Intel4004::bbl<0b11000110>,
&Intel4004::bbl<0b11000111>,
&Intel4004::bbl<0b11001000>,
&Intel4004::bbl<0b11001001>,
&Intel4004::bbl<0b11001010>,
&Intel4004::bbl<0b11001011>,
&Intel4004::bbl<0b11001100>,
&Intel4004::bbl<0b11001101>,
&Intel4004::bbl<0b11001110>,
&Intel4004::bbl<0b11001111>,
&Intel4004::ldm<0b11010000>,
&Intel4004::ldm<0b11010001>,
&Intel4004::ldm<0b11010010>,
&Intel4004::ldm<0b11010011>,
&Intel4004::ldm<0b11010100>,
&Intel4004::ldm<0b11010101>,
&Intel4004::ldm<0b11010110>,
&Intel4004::ldm<0b11010111>,
&Intel4004::ldm<0b11011000>,
&Intel4004::ldm<0b11011001>,
&Intel4004::ldm<0b11011010>,
&Intel4004::ldm<0b11011011>,
&Intel4004::ldm<0b11011100>,
&Intel4004::ldm<0b11011101>,
&Intel4004::ldm<0b11011110>,
&Intel4004::ldm<0b11011111>,
&Intel4004::wrm<0b11100000>,
&Intel4004::wmp<0b11100001>,
&Intel4004::wrr<0b11100010>,
NULL,
&Intel4004::wr0<0b11100100>,
&Intel4004::wr1<0b11100101>,
&Intel4004::wr2<0b11100110>,
&Intel4004::wr3<0b11100111>,
&Intel4004::sbm<0b11101000>,
&Intel4004::rdm<0b11101001>,
&Intel4004::rdr<0b11101010>,
&Intel4004::adm<0b11101011>,
&Intel4004::rd0<0b11101100>,
&Intel4004::rd1<0b11101101>,
&Intel4004::rd2<0b11101110>,
&Intel4004::rd3<0b11101111>,
&Intel4004::clb<0b11110000>,
&Intel4004::clc<0b11110001>,
&Intel4004::iac<0b11110010>,
&Intel4004::cmc<0b11110011>,
&Intel4004::cma<0b11110100>,
NULL,
&Intel4004::rar<0b11110110>,
&Intel4004::tcc<0b11110111>,
&Intel4004::dac<0b11111000>,
&Intel4004::tcs<0b11111001>,
&Intel4004::stc<0b11111010>,
&Intel4004::daa<0b11111011>,
&Intel4004::kbp<0b11111100>,
&Intel4004::dcl<0b11111101>,
NULL,
NULL};
Intel4004::Intel4004()
{
for(auto i = 0ul; i < 4096; i ++)
rom_mem[i] = bitset(0,8);
for(auto i = 0ul; i < 2048; i ++)
ram_mem[i] = bitset(0,4);
for(auto i = 0ul; i < 512; i ++)
ram_status_mem[i] = bitset(0,4);
for(auto i = 0ul; i < 32; i ++)
ram_port_mem[i] = bitset(0,4);
for(auto i = 0ul; i < 16; i ++)
rom_port_mem[i] = bitset(0,4);

}
const char* Intel4004::bin(AddressInfo info)
{
       return get(info).bin();
    }
const char* Intel4004::hex(AddressInfo info)
{
       return get(info).hex();
    }
const char* Intel4004::dec(AddressInfo info)
{
       return get(info).dec();
    }
void Intel4004::display()
{
#ifndef NO_PRINT
printf("         STACK                REGISTERS\n\
    PC %s          R0 R1 %s %s   R8 R9 %s %s\n\
LEVEL 1 %s          R2 R3 %s %s   RA RB %s %s\n\
LEVEL 2 %s          R4 R5 %s %s   RA RB %s %s\n\
LEVEL 3 %s          R6 R7 %s %s   RA RB %s %s\n\
\n\
ACCUMULATOR: %s [%s]  CARRY: %s\n",hex(PC),hex(R0),hex(R1),hex(R8),hex(R9),hex(STACK0),hex(R2),hex(R3),hex(R10),hex(R11),hex(STACK1),hex(R4),hex(R5),hex(R12),hex(R13),hex(STACK2),hex(R6),hex(R7),hex(R14),hex(R15),dec(ACC),bin(ACC),bin(CY));
#endif
}
void Intel4004::simulate(SIZE_T i)
{
for (;i-->0;)
{
   auto val = fetch();
   if(ops[val.val()] == NULL)
   {
   #ifndef NO_PRINT
   fprintf(stderr, "%s unknown\n", val.bin());
   #endif
   break;
   }
   (this->*ops[val.val()])();
}
}
bitset& Intel4004::rom(AddressInfo info)
{
return rom(get(info));
}

bitset& Intel4004::rom(bitset index)
{
return rom_mem[index.val()];
}
#ifndef C_ONLY
void Intel4004::flash_rom(std::vector<bitset> data)
{
for(auto i = 0ul; i < data.size(); i++)
rom_mem[i] = bitset(data[i], 8);
}

#endif
void Intel4004::flash_rom(bitset* data, SIZE_T len)
{
for(auto i = 0ul; i < len; i++)
rom_mem[i] = bitset(data[i], 8);
}

bitset& Intel4004::ram(AddressInfo info)
{
return ram(get(info));
}

bitset& Intel4004::ram(bitset index)
{
return ram_mem[index.val()];
}
#ifndef C_ONLY
void Intel4004::flash_ram(std::vector<bitset> data)
{
for(auto i = 0ul; i < data.size(); i++)
ram_mem[i] = bitset(data[i], 4);
}

#endif
void Intel4004::flash_ram(bitset* data, SIZE_T len)
{
for(auto i = 0ul; i < len; i++)
ram_mem[i] = bitset(data[i], 4);
}

bitset& Intel4004::ram_status(AddressInfo info)
{
return ram_status(get(info));
}

bitset& Intel4004::ram_status(bitset index)
{
return ram_status_mem[index.val()];
}
#ifndef C_ONLY
void Intel4004::flash_ram_status(std::vector<bitset> data)
{
for(auto i = 0ul; i < data.size(); i++)
ram_status_mem[i] = bitset(data[i], 4);
}

#endif
void Intel4004::flash_ram_status(bitset* data, SIZE_T len)
{
for(auto i = 0ul; i < len; i++)
ram_status_mem[i] = bitset(data[i], 4);
}

bitset& Intel4004::ram_port(AddressInfo info)
{
return ram_port(get(info));
}

bitset& Intel4004::ram_port(bitset index)
{
return ram_port_mem[index.val()];
}
#ifndef C_ONLY
void Intel4004::flash_ram_port(std::vector<bitset> data)
{
for(auto i = 0ul; i < data.size(); i++)
ram_port_mem[i] = bitset(data[i], 4);
}

#endif
void Intel4004::flash_ram_port(bitset* data, SIZE_T len)
{
for(auto i = 0ul; i < len; i++)
ram_port_mem[i] = bitset(data[i], 4);
}

bitset& Intel4004::rom_port(AddressInfo info)
{
return rom_port(get(info));
}

bitset& Intel4004::rom_port(bitset index)
{
return rom_port_mem[index.val()];
}
#ifndef C_ONLY
void Intel4004::flash_rom_port(std::vector<bitset> data)
{
for(auto i = 0ul; i < data.size(); i++)
rom_port_mem[i] = bitset(data[i], 4);
}

#endif
void Intel4004::flash_rom_port(bitset* data, SIZE_T len)
{
for(auto i = 0ul; i < len; i++)
rom_port_mem[i] = bitset(data[i], 4);
}

bitset Intel4004::fetch()
{
/* rom(PC)*/
return rom(get(PC));
}
void Intel4004::set(bitset data, AddressInfo info)
{
set_mem(&memory[0], info, data);
}
void Intel4004::set(bitset data, bitset& dest)
{
dest=data;
}
void Intel4004::set(bitset data, int num, ...)
{
va_list valist;
va_start(valist, num);
for(SIZE_T i = num; i --> 0;)
{
AddressInfo info = va_arg(valist, AddressInfo);
set_mem(&memory[0], info, data);
data = data >> info.length;
va_end(valist);
}
}
