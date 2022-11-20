#include <Arduino.h>
#include "abitset.hpp"
#include "AddressInfo.hpp"
#include "AddressInfos.hpp"
#include "bitset.hpp"
#include "Intel4004.hpp"
void setup()
{
  Serial.begin(9600);
  while(Serial.available());



  // put your setup code here, to run once:
}
  Intel4004 cpu{};

void loop()
{
      bitset prog[] = {0x28, 0x00, 0x29, 0xEA, 0xB0, 0x68, 0x29, 0xEA, 0xB1, 0x50, 0x68, 0xB2, 0xE1, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xB2, 0xD4, 0xB0, 0xF6, 0xB0, 0x1A, 0x7A, 0xB1, 0xF6, 0xB1, 0xB2, 0xF6, 0xB2, 0xF8, 0x1C, 0x6B, 0xC0, 0xB1, 0xF6, 0xB1, 0xF1, 0x40, 0x73}; 
    cpu.flash_rom(prog, sizeof(prog) / sizeof(bitset));
        delay(100);
        Serial.write("=====================\n");
    

    // char buffer[100] = {};
    // cpu.set(4,ACC);
    // cpu.display();
    // (cpu.get(ACC),cpu.get(R0)).hex(buffer);
    // Serial.println(buffer);

    // cpu.set(((cpu.get(ACC),cpu.get(R0))), 2,ACC,R0);

    // (cpu.get(ACC),cpu.get(R0)).hex(buffer);
    // Serial.println(buffer);

    for (int i = 100; i --> 0;)
    {
        cpu.simulate(1);
    }
            Serial.write("a\n");

        cpu.display();
    
  exit(0);

}