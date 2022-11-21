#include <iostream>
#include <iomanip>
#include "gasm.hpp"
#include "argument_parser.hpp"
#include <fstream>
#include <filesystem>

int main(int argc, char **argv)
{
    ArgumentParser parser(argc,argv);

    GeneralAssembler gasm = GeneralAssembler();

    std::string code_file = parser.getCode();
    std::string cpu_file = parser.getCPU();
    std::string out_file = parser.getOut();

    
    std::vector<int> assembled_code = gasm.assemble(code_file, cpu_file);
    std::filesystem::create_directories(std::filesystem::path(out_file).parent_path());
    std::ofstream out(out_file);

    for (size_t i = 0; i < assembled_code.size(); i++)
        out << (char)assembled_code[i];
    
    out.close();
    return 0;
}
