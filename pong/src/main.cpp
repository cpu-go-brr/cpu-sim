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
    while (true)
    {
        for (int j = 0; j < 20; j++)
            cpu.simulate();
        cpu.display();

        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 16; i++)
                std::cout << cpu.ram_mem[16*j +i].val();
            std::cout << "\n";
        }
        tty.read(&c, 1);
    }
    return 0;
}
