#include <string>
#include <map>
#include <vector>

class Intel4004
{
    public:
        Intel4004(){};
        void simultate(); //Simulate sall available code
        void feed(std::string assembler); //add assembler


    private:
        long pc;
        
        std::vector<char> code;
        
};