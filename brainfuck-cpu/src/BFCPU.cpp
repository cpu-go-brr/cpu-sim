#include "BFCPU.hpp"
#include <stdio.h>
#include <stdlib.h>
/* No Operation*/
template <>
void BFCPU::nop<0b00000000>()
{
}


/* Increment the data pointer (to point to the next cell to the right).*/
template <>
void BFCPU::right<0b00000001>()
{
/* PTR + 1 --> PTR*/
set((get(PTR)+1), PTR);
/* PC + 1 --> PC*/
set((get(PC)+1), PC);
}


/* Decrement the data pointer (to point to the next cell to the left).*/
template <>
void BFCPU::left<0b00000010>()
{
/* PTR + 255 --> PTR*/
set((get(PTR)+255), PTR);
/* PC + 1 --> PC*/
set((get(PC)+1), PC);
}


/* Increment (increase by one) the byte at the data pointer.*/
template <>
void BFCPU::inc<0b00000011>()
{
/* band(PTR) + 1 --> band(PTR)*/
set((band(get(PTR))+1), band(get(PTR)));
/* PC + 1 --> PC*/
set((get(PC)+1), PC);
}


/* Decrement (decrease by one) the byte at the data pointer.*/
template <>
void BFCPU::dec<0b00000100>()
{
/* band(PTR) + 255 --> band(PTR)*/
set((band(get(PTR))+255), band(get(PTR)));
/* PC + 1 --> PC*/
set((get(PC)+1), PC);
}


/* Output the byte at the data pointer.*/
template <>
void BFCPU::print<0b00000101>()
{
/* band(PTR) --> VAL*/
set((band(get(PTR))), VAL);
/* 1 --> SEND*/
set((1), SEND);
/* PC + 1 --> PC*/
set((get(PC)+1), PC);
}


/* Accept one byte of input, storing its value in the byte at the data pointer.*/
template <>
void BFCPU::read<0b00000110>()
{
/* VAL --> band(PTR)*/
set((get(VAL)), band(get(PTR)));
/* 1 --> READ*/
set((1), READ);
/* PC + 1 --> PC*/
set((get(PC)+1), PC);
}


/* If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.*/
template <>
void BFCPU::loop<0b00000111>()
{
/* band(PTR) == 0 ? rom(PC +1) --> PC*/
if(band(get(PTR))==0)
{
set((rom(get(PC)+1)), PC);
}
/* band(PTR) != 0 ? PC+2--> PC*/
if(band(get(PTR))!=0)
{
set((get(PC)+2), PC);
}
}


/* Return to the matching [ command.*/
template <>
void BFCPU::ret<0b00001000>()
{
/* rom(PC +1) --> PC*/
set((rom(get(PC)+1)), PC);
}


BFCPU::op BFCPU::ops[256] = {
&BFCPU::nop<0b00000000>,
&BFCPU::right<0b00000001>,
&BFCPU::left<0b00000010>,
&BFCPU::inc<0b00000011>,
&BFCPU::dec<0b00000100>,
&BFCPU::print<0b00000101>,
&BFCPU::read<0b00000110>,
&BFCPU::loop<0b00000111>,
&BFCPU::ret<0b00001000>,
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
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL};
BFCPU::BFCPU()
{
for(auto i = 0ul; i < 256; i ++)
rom_mem[i] = bitset(0,8);
for(auto i = 0ul; i < 256; i ++)
band_mem[i] = bitset(0,8);

}
void BFCPU::bin(AddressInfo info, char* addr)
{
       get(info).bin(addr);
    }
void BFCPU::hex(AddressInfo info, char* addr)
{
       get(info).hex(addr);
    }
void BFCPU::dec(AddressInfo info, char* addr)
{
       get(info).dec(addr);
    }
char* BFCPU::display()
{
if(str == NULL)
{
str = (char*)malloc(33);
sprintf(str, "PC: XX PTR: XX OUT: XXX SEND: X\n\
");
}
hex(PC, str +4);
hex(PTR, str +12);
hex(OUT, str +20);
hex(SEND, str +30);
#ifndef NO_PRINT
printf("%s",str);
#endif
return str;
}
void BFCPU::simulate(size_t i)
{
for (;i-->0;)
{
   auto val = fetch();
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
bitset& BFCPU::rom(AddressInfo info)
{
return rom(get(info));
}

bitset& BFCPU::rom(bitset index)
{
return rom_mem[index.val()];
}
#ifndef NO_CPPSTD
void BFCPU::flash_rom(std::vector<bitset> data)
{
for(auto i = 0ul; i < data.size(); i++)
rom_mem[i] = bitset(data[i], 8);
}

#endif
void BFCPU::flash_rom(bitset* data, size_t len)
{
for(auto i = 0ul; i < len; i++)
rom_mem[i] = bitset(data[i], 8);
}

bitset& BFCPU::band(AddressInfo info)
{
return band(get(info));
}

bitset& BFCPU::band(bitset index)
{
return band_mem[index.val()];
}
#ifndef NO_CPPSTD
void BFCPU::flash_band(std::vector<bitset> data)
{
for(auto i = 0ul; i < data.size(); i++)
band_mem[i] = bitset(data[i], 8);
}

#endif
void BFCPU::flash_band(bitset* data, size_t len)
{
for(auto i = 0ul; i < len; i++)
band_mem[i] = bitset(data[i], 8);
}

bitset BFCPU::fetch()
{
/* 0 --> SEND*/
set((0), SEND);
/* 0 --> READ*/
set((0), READ);
/* 0 --> VAL*/
set((0), VAL);
/* rom(PC)*/
return rom(get(PC));
}
void BFCPU::set(bitset data, AddressInfo info)
{
set_mem(&memory[0], info, data);
}
void BFCPU::set(bitset data, bitset& dest)
{
dest=bitset(data,dest.size());
}
void BFCPU::set(bitset data, int num, const AddressInfo* infos)
{
for(size_t i = num; i --> 0;)
{
set_mem(&memory[0], infos[i], data);
data = data >> infos[i].length;
}
}
bitset BFCPU::get(AddressInfo info)
{
   return get_mem(&memory[0], info);
}
#ifndef NO_CPPSTD
    std::string BFCPU::json()
{
std::string json = "{\"internal\":{"
"\"PC\":{\"bits\":8,\"val\":" + std::to_string(get(PC).val()) + "},"
"\"PTR\":{\"bits\":8,\"val\":" + std::to_string(get(PTR).val()) + "},"
"\"OUT\":{"
"\"VAL\":{\"bits\":8,\"val\":" + std::to_string(get(VAL).val()) + "},"
"\"SEND\":{\"bits\":1,\"val\":" + std::to_string(get(SEND).val()) + "},"
"\"READ\":{\"bits\":1,\"val\":" + std::to_string(get(READ).val()) + "}"
"}},\"external\":{"
"\"rom\":{\"bits\":8,\"vals\":[";
for(size_t i = 0; i < 256; i++) json += std::to_string(rom_mem[i].val()) + ",";
json = json.substr(0,json.size()-1);
json += "]},";
json +="\"band\":{\"bits\":8,\"vals\":[";
for(size_t i = 0; i < 256; i++) json += std::to_string(band_mem[i].val()) + ",";
json = json.substr(0,json.size()-1);
json += "]"
"}}";
return json + "}";
}
#endif
