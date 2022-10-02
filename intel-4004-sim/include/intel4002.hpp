#include <string>
#include <map>
#include <vector>
#include <optional>

//RAM
class Intel4002
{
    public:
        uint8_t get(uint8_t addr);
        void set(uint8_t addr, uint8_t val);
    private:
        uint8_t mem[4][4][16]; //chip/register/adress
        uint8_t out;
};

