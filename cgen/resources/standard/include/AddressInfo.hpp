#pragma once

#include "bitset.hpp"

typedef struct AddressInfo
{
   size_t byte_start = 0;
   size_t bit_offset = 0;
   size_t length = 0;

   AddressInfo(int byte, int bit, int len)
       : byte_start(byte), bit_offset(bit), length(len) {}

} AddressInfo;

size_t bytes_needed(const AddressInfo &i);

bitset get_mem(uint8_t *mem, const AddressInfo &info);

void set_mem(uint8_t *mem, const AddressInfo &info, const bitset &data);