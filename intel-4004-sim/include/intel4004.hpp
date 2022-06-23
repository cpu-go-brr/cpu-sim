#include <string>
#include <map>
#include <vector>

class Intel4004
{

    typedef void (Intel4004::*op)();

    public:
        Intel4004(){};
        void simultate(); //Simulate sall available code
        void feed(std::string assembler); //add assembler

    private:
        uint16_t pc; //12 bit
        uint16_t sr1, sr2, sr3; //12 bit stack level registers
        uint8_t acc; //4 bit accumulator

        uint8_t registers[16]; //16 4 bit registers

        uint8_t prog_mem[4096];
        uint8_t data_mem[640];
        
        std::vector<char> code;

        //operations
};

