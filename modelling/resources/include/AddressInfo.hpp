#pragma once

#include <stdint.h>
#include "bitset.hpp"
#include <cmath>

typedef struct AddressInfo
{
   std::size_t byte_start = 0;
   std::size_t bit_offset = 0;
   std::size_t length = 0;
} AddressInfo;


std::size_t bytes(AddressInfo i);

bitset get_mem(uint8_t *mem, AddressInfo info);

void set_mem(uint8_t *mem, AddressInfo info, bitset data);