#pragma once

#include <stdint.h>
#include "bitset.hpp"
#include <cmath>

typedef struct AddressInfo
{
   uint8_t byte_start = 0;
   uint8_t bit_offset = 0;
   uint8_t length = 0;
} AddressInfo;

std::size_t bytes(AddressInfo i)
{
   return (std::size_t)std::ceil((i.length + i.bit_offset) / 8.0);
}

bitset get_mem(uint8_t *mem, AddressInfo info)
{
   std::vector<uint8_t> data;
   for (std::size_t i = 0; i < bytes(info); i++)
   {
      data.push_back(mem[info.byte_start + i]);
   }

   bitset ret{data, (std::size_t)info.length + (std::size_t)info.bit_offset};
   ret = ret >> info.bit_offset;

   return bitset(ret, info.length);
}

void set_mem(uint8_t *mem, AddressInfo info, bitset data)
{
   bitset shifted{data, (std::size_t)info.length + (std::size_t)info.bit_offset};
   shifted = shifted << info.bit_offset;

   auto mask_vector = std::vector<uint8_t>(bytes(info), 0xFF);

   mask_vector[bytes(info)-1] &= ((1 << (info.length % 8)) -1);

   bitset mask{mask_vector, (std::size_t)info.bit_offset + (std::size_t)info.length};
   mask = mask << info.bit_offset;


   for (std::size_t i = 0; i < bytes(info); i++)
   {
      uint8_t original_data = mem[info.byte_start + i];
      mem[info.byte_start + i] = (original_data & ~mask[i]) | (shifted[i] & mask[i]);
   }
}