#include "AddressInfo.hpp"

std::size_t bytes_needed(const AddressInfo& i)
{
   return (std::size_t)std::ceil((i.length + i.bit_offset) / 8.0);
}

bitset get_mem(uint8_t *mem, const AddressInfo& info)
{
   bitset ret{&mem[info.byte_start], (bitset::bits_t)bytes_needed(info), (bitset::bits_t)(info.length + info.bit_offset)};
   return bitset(ret >> info.bit_offset, info.length);
}

void set_mem(uint8_t *mem, const AddressInfo& info, const bitset& data)
{
   data.write(mem, info);

/*
   bitset shifted{data << info.bit_offset, (bitset::bits_t)(info.length + info.bit_offset)};

   uint8_t mask_vector[bytes_needed(info)];
   for(auto i = bytes_needed(info)-1; i --> 0;) mask_vector[i] = 0xFF;

   bitset mask{mask_vector, (bitset::bits_t)(info.bit_offset + info.length)};
   mask = mask << info.bit_offset;

   if( (info.length + info.bit_offset) % 8 != 0) // alignment needs masking
      mask[bytes_needed(info)-1] &= ((1 << ((info.length + info.bit_offset) % 8)) -1);

   for (std::size_t i = 0; i < bytes_needed(info); i++)
   {
      uint8_t original_data = mem[info.byte_start + i];
      mem[info.byte_start + i] = (original_data & ~mask[i]) | (shifted[i] & mask[i]);
   }
*/
}