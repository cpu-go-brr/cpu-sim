#pragma once

#include "intel4001.hpp"
#include "intel4002.hpp"
#include "intel4004.hpp"


class System
{
    public:
        void flash_rom(int rom, std::string code);
        void display();
        

    private:
        Intel4001 rom[16];
        Intel4002 mem[4];
        Intel4004 cpu;


};

