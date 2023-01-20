#include "${CPU_NAME}.hpp"
#include "gasm.hpp"
#include <emscripten/emscripten.h>

${CPU_NAME} cpu;
GenericAssembler ga;

std::string ret;
extern "C" EMSCRIPTEN_KEEPALIVE const char* json() 
{
    ret = cpu.json();
    return ret.c_str();
}

extern "C" EMSCRIPTEN_KEEPALIVE void simulate() 
{
    cpu.simulate();
}

extern "C" EMSCRIPTEN_KEEPALIVE void assemble(char * source) 
{
    auto ints = ga.assemble_string(req.get_param_value("code"));
    std::vector<bitset> bitsets;
    for(auto i : ints)
        bitsets.push_back(i);
    cpu.flash_rom(bitsets);
}

extern "C" EMSCRIPTEN_KEEPALIVE void reset() 
{
    cpu ={};
}