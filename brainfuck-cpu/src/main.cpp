#include "BFCPU.hpp"

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

    BFCPU cpu;

    cpu.flash_rom(prog);

    std::ifstream tty("/dev/tty");
    char c;
    while (true)
    {
        cpu.simulate();
        cpu.display();

        tty.read(&c, 1);
    }
    return 0;
}
