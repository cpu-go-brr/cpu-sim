#pragma once

#include <stdint.h>
#include "fbitset.hpp"

typedef struct AddressInfo
{
   uint32_t byte_start = 0;
   uint32_t bit_offset = 0;
   uint32_t length = 0;
} AddressInfo;

uint32_t bytes_needed(const AddressInfo &i);

fbitset get_mem(uint8_t *mem, const AddressInfo &info);

void set_mem(uint8_t *mem, const AddressInfo &info, const fbitset &data);