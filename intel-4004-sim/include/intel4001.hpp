#include <string>
#include <map>
#include <vector>
#include <optional>

//ROM
class Intel4001
{
    public:
        uint8_t write(uint8_t addr);
        void set(uint8_t addr, uint8_t val);
    private:
        uint8_t mem[256]; //chip/register/adress
        uint8_t out;
};

