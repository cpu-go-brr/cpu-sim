#include "AddressInfo.hpp"

size_t bytes_needed(const AddressInfo& i)
{
   return (size_t)((i.length + i.bit_offset) / 8.0 + ((i.length + i.bit_offset) % 8 > 0?1:0));
}

bitset get_mem(uint8_t *mem, const AddressInfo& info)
{
   bitset ret{&mem[info.byte_start], (bitset::bits_t)bytes_needed(info), (bitset::bits_t)(info.length + info.bit_offset)};
   return bitset(ret >> info.bit_offset, info.length);
}

void set_mem(uint8_t *mem, const AddressInfo& info, const bitset& data)
{
   data.write(mem, info);
}