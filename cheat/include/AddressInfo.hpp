#pragma once

#include "bitset.hpp"
#include "size_t.hpp"

typedef struct AddressInfo
{
   SIZE_T byte_start = 0;
   SIZE_T bit_offset = 0;
   SIZE_T length = 0;

   AddressInfo(int byte, int bit, int len)
       : byte_start(byte), bit_offset(bit), length(len) {}

} AddressInfo;

SIZE_T bytes_needed(const AddressInfo &i);

bitset get_mem(uint8_t *mem, const AddressInfo &info);

void set_mem(uint8_t *mem, const AddressInfo &info, const bitset &data);