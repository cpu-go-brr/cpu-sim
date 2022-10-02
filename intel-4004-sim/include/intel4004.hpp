#include <string>
#include <map>
#include <vector>
#include <optional>

//CPU
class Intel4004
{
    public:
        Intel4004(){};
        void simultate(); //Simulate one command
        void feed(std::string assembler); //add assembler

        void set_object_code(std::vector<uint8_t> code);
        void print_status();


    private:

        bool carry = false, test = false;
        uint8_t read_rom(unsigned int pos);

        typedef void (Intel4004::*op)();

        uint16_t pc = 0; //12 bit
        uint16_t sr1 = 0, sr2 = 0, sr3 = 0; //12 bit stack level registers
        uint8_t acc = 0; //4 bit accumulator

        bool testpin = 0;

        uint8_t reg_ctl = 0; //2b -> chip | 2b -> register | 4b -> addr 
        uint8_t registers[16] = {0}; //16 4 bit registers
        
        std::vector<uint8_t> code;

        void execute_function();

        #define insert_multiple(prefix,suffix,name) \
        {prefix##000##suffix, name}, \
        {prefix##001##suffix, name}, \
        {prefix##010##suffix, name}, \
        {prefix##011##suffix, name}, \
        {prefix##100##suffix, name}, \
        {prefix##101##suffix, name}, \
        {prefix##110##suffix, name}, \
        {prefix##111##suffix, name} \


        std::map<int, Intel4004::op> ops = 
        {
            {0b0000,         &Intel4004::nop},
            {0b0001,         &Intel4004::jcn},
            insert_multiple(0b0010,0,&Intel4004::fim),
            insert_multiple(0b0010,1,&Intel4004::src),
            insert_multiple(0b0011,0,&Intel4004::fin),
            insert_multiple(0b0011,1,&Intel4004::jin),
            {0b0100,    &Intel4004::jun},
            {0b0101,    &Intel4004::jms},
            {0b0110,    &Intel4004::inc},
            {0b0111,    &Intel4004::isz},
            {0b1000,    &Intel4004::add},
            {0b1001,    &Intel4004::sub},
            {0b1010,    &Intel4004::ld},
            {0b1011,    &Intel4004::xch},
            {0b1100,    &Intel4004::bbl},
            {0b1101,    &Intel4004::ldm},
            {0b11100000,    &Intel4004::wrm},
            {0b11100001,    &Intel4004::wmp},
            {0b11100010,    &Intel4004::wrr},
            {0b11100100,    &Intel4004::wr0},
            {0b11100101,    &Intel4004::wr1},
            {0b11100110,    &Intel4004::wr2},
            {0b11100111,    &Intel4004::wr3},
            {0b11101000,    &Intel4004::sbm},
            {0b11101001,    &Intel4004::rdm},
            {0b11101010,    &Intel4004::rdr},
            {0b11101011,    &Intel4004::adm},
            {0b11101100,    &Intel4004::rd0},
            {0b11101101,    &Intel4004::rd1},
            {0b11101110,    &Intel4004::rd2},
            {0b11101111,    &Intel4004::rd3},
            {0b11110000,    &Intel4004::clb},
            {0b11110001,    &Intel4004::clc},
            {0b11110010,    &Intel4004::iac},
            {0b11110011,    &Intel4004::cmc},
            {0b11110100,    &Intel4004::cma},
            {0b11110101,    &Intel4004::ral},
            {0b11110110,    &Intel4004::rar},
            {0b11110111,    &Intel4004::tcc},
            {0b11111000,    &Intel4004::dac},
            {0b11111001,    &Intel4004::tcs},
            {0b11111010,    &Intel4004::stc},
            {0b11111011,    &Intel4004::daa},
            {0b11111100,    &Intel4004::kbp},
            {0b11111101,    &Intel4004::dcl},
        };

        //operations one word
        void nop();
        void ldm();
        void ld();
        void xch();
        void add();
        void sub();
        void inc();
        void bbl();
        void jin();
        void src();
        void fin();

        //operations two word
        void jun();
        void jms();
        void jcn();
        void isz();
        void fim();

        //IO Instructions
        void rdm();
        void rd0();
        void rd1();
        void rd2();
        void rd3();
        void rdr();
        void wrm();
        void wr0();
        void wr1();
        void wr2();
        void wr3();
        void wrr();
        void wmp();
        void adm();
        void sbm();

        //acc group instructions
        void clb();
        void clc();
        void cmc();
        void stc();
        void cma();
        void iac();
        void dac();
        void ral();
        void rar();
        void tcc();
        void daa();
        void tcs();
        void kbp();
        void dcl();
    


};

