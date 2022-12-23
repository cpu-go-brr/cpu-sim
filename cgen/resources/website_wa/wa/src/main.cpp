#include "${CPU_NAME}.hpp"
#include <emscripten/emscripten.h>

${CPU_NAME} cpu;

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


extern "C" EMSCRIPTEN_KEEPALIVE void reset() 
{
    cpu ={};
}