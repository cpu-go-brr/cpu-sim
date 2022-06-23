#include "../include/parsing.hpp"
#include <iostream>
#include <fstream>

void Intel4004Parser::parse(std::string file_path, bool debug){
    if(debug) std::cout << "Parsing..." << "\n";
    std::string asm_intruction;
    std::ifstream asm_instruction_file (file_path);

    if(!asm_instruction_file){
        std::cout << "Failed to load file" << "'" << file_path << "'" << "\n";
        return;
    }

    while (getline (asm_instruction_file, asm_intruction)) {
        if(debug) std::cout << asm_intruction << "\n";

        // actual parsing of string
    }

    asm_instruction_file.close();
}

