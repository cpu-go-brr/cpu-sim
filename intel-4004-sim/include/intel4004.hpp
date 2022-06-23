#include <string>
#include <map>
#include <vector>

class Intel4004
{
    public:
        Intel4004(){};
        void simultate(); //Simulate one command
        void feed(std::string assembler); //add assembler

        void set_object_code(std::vector<uint8_t> code);
        void print_status();


    private:
        typedef void (Intel4004::*op)();

        uint16_t pc = 0; //12 bit
        uint16_t sr1 = 0, sr2 = 0, sr3 = 0; //12 bit stack level registers
        uint8_t acc = 0; //4 bit accumulator

        uint8_t registers[16] = {0}; //16 4 bit registers

        uint8_t prog_mem[4096] = {0};
        uint8_t data_mem[640] = {0};
        
        std::vector<uint8_t> code;

        void execute_function();

        std::map<int, Intel4004::op> ops = 
        {
            {0, &Intel4004::nop}
        };

        //operations
        void nop();
};

