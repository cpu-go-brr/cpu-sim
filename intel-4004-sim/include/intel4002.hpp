#pragma once

#include <string>
#include <map>
#include <vector>
#include <optional>

//RAM
class Intel4002
{
    public:
        uint8_t mem[4][16]{}; //chip/register/adress
        uint8_t status[4][4]{}; //chip/register/adress
        uint8_t out;
};

