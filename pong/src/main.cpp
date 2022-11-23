#include "Intel4004.hpp"

#include <fstream>
int main(int argc, char **argv)
{
    std::vector<unsigned char> bytes;
    if (argc == 1)
    {
        char c;
        while (std::cin.get(c))
            bytes.push_back(c); // loop getting single characters
    }
    else if (argc == 2)
    {
        std::ifstream input(argv[1], std::ios::binary);
        bytes = std::vector<unsigned char>((std::istreambuf_iterator<char>(input)),
                                           std::istreambuf_iterator<char>());
    }
    else
    {
        exit(0);
    }
    std::vector<bitset> prog;
    for (const auto c : bytes)
        prog.push_back(c);

    Intel4004 cpu;

    cpu.flash_rom(prog);

    std::ifstream tty("/dev/tty");
    char c;

    char rom_port[5] = "XXXX";
    while (true)
    {
        cpu.rom_port(0).bin(rom_port);
        cpu.simulate();
        cpu.display();

        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 16; i++)
                std::cout << cpu.ram_mem[16*j +i].val();
            std::cout << "\n";
        }
        std::cout << "rom_port: "<< rom_port << "\n"; 

        //Player 1: wsx Player 2: ujm

        while(tty.read(&c, 1))
        {
            if(c == '\n') break;
            uint8_t val = cpu.rom_port(0).val();

            if(c == 'w') cpu.set(0b1000 + (val & 0b11), cpu.rom_port(0));
            if(c == 's') cpu.set(0b0000 + (val & 0b11), cpu.rom_port(0));
            if(c == 'x') cpu.set(0b0100 + (val & 0b11), cpu.rom_port(0));


            if(c == 'u') cpu.set(0b10 + (val & 0b1100), cpu.rom_port(0));
            if(c == 'j') cpu.set(0b00 + (val & 0b1100), cpu.rom_port(0));
            if(c == 'm') cpu.set(0b01 + (val & 0b1100), cpu.rom_port(0));

        }


    }
    return 0;
}
