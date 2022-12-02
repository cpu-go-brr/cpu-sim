#include <Arduino.h>
#include "Intel4004.hpp"
Intel4004 cpu{};

void draw();

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);

    bitset prog[] = {0x50, 0x13, 0x50, 0x0E, 0x50, 0x91, 0x50, 0x62, 0x50, 0x32, 0x40, 0x02, 0x40, 0x2E, 0x26, 0xFF, 0x26, 0x00, 0xC0, 0x2C, 0x37, 0x2E, 0x11, 0x2A, 0x54, 0x20, 0x00, 0xF0, 0x2D, 0xD1, 0xE0, 0xAA, 0xB0, 0x21, 0xD2, 0xE0, 0xAB, 0xB0, 0xDF, 0xB1, 0x21, 0xD2, 0xE0, 0x20, 0x00, 0xC0, 0x50, 0x0E, 0x40, 0x2E, 0x20, 0x00, 0x21, 0xEA, 0xF6, 0x1A, 0x4C, 0xF1, 0xD7, 0x9B, 0x14, 0x4C, 0xAB, 0xB0, 0xDF, 0xB1, 0x21, 0xD0, 0xE0, 0x6B, 0xAB, 0xB0, 0x21, 0xD2, 0xE0, 0xC0, 0xF6, 0x1A, 0x61, 0xF1, 0xAB, 0x14, 0x61, 0xB0, 0xDF, 0xB1, 0x21, 0xD0, 0xE0, 0xAB, 0xF8, 0xBB, 0xAB, 0xB0, 0x21, 0xD2, 0xE0, 0xC0, 0x20, 0x00, 0x21, 0xEA, 0xF5, 0x1A, 0x7B, 0xF1, 0xAA, 0x14, 0x7B, 0xB0, 0xD0, 0xB1, 0x21, 0xD0, 0xE0, 0xAA, 0xF8, 0xBA, 0xAA, 0xB0, 0x21, 0xD2, 0xE0, 0xF5, 0x1A, 0x90, 0xF1, 0xD7, 0x9A, 0x14, 0x90, 0xAA, 0xB0, 0xD0, 0xB1, 0x21, 0xD0, 0xE0, 0x6A, 0xAA, 0xB0, 0x21, 0xD2, 0xE0, 0xC0, 0xAC, 0xB0, 0xAD, 0xB1, 0xAD, 0xF2, 0xF4, 0x1C, 0xA2, 0xF1, 0xAB, 0x90, 0x1C, 0xA2, 0xF0, 0x9E, 0xBE, 0xAD, 0xF8, 0x1C, 0xAE, 0xF1, 0xAA, 0x90, 0x1C, 0xAE, 0xF0, 0x9E, 0xBE, 0xAC, 0x1C, 0xB4, 0xF0, 0x9F, 0xBF, 0xD7, 0xF1, 0x9C, 0x1C, 0xBC, 0xF0, 0x9F, 0xBF, 0xAD, 0xF1, 0x8E, 0xBD, 0xAC, 0xF1, 0x8F, 0xBC, 0x21, 0xD0, 0xE0, 0x2D, 0xD1, 0xE0, 0xAD, 0x14, 0x2E, 0xF4, 0x14, 0x2E, 0xC0};
    cpu.flash_rom(prog, sizeof(prog) / sizeof(bitset));
}

void draw()
{
    // printf("%s\n", cpu.display());
    //  char rom_port[5] = "XXXX";
    //  cpu.rom_port(0).bin(rom_port);
    char str[2];
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            cpu.ram_mem[x + 16 * y].hex(str);
            printf("%s", str);
        }
        printf("\n");
    }
    // printf("\nrom_port: %s\n", rom_port);
    printf("\n\n");
}
void loop()
{
    while (cpu.get(R6).val() == 0)
        cpu.simulate();

    cpu.simulate();

    draw();
    delay(1000);

    // while (!Serial.available())
    //     ;

    // while (Serial.available())
    //     Serial.read();
}
