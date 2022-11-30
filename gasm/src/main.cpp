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
    std::string format_param = parser.getFormat();

    
    std::vector<int> assembled_code = gasm.assemble(code_file, cpu_file);
    std::filesystem::create_directories(std::filesystem::path(out_file).parent_path());
    std::ofstream out(out_file);

    for (size_t i = 0; i < assembled_code.size(); i++)
    {
        if(format_param == "bin")
            out << (char)assembled_code[i];
        if(format_param == "c")
        {
            out << "0x"; 
            out << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << assembled_code[i];
            if(i != assembled_code.size()-1)
            out << ",";
        }
        if(format_param == "hex")
            out << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << assembled_code[i] << " ";
    }

    if(format_param != "bin") out << "\n";
    
    out.close();
    return 0;
}
