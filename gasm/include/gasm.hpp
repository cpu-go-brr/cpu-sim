#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class GenericAssembler{

    public:
        GenericAssembler(){};
        std::vector<int> assemble_file(std::string asm_file_path, std::string yaml_file_path);
        std::vector<int> assemble_file(std::string asm_file_path);
        std::vector<int> assemble_string(std::string asm_string, std::string yaml_file_path);
        std::vector<int> assemble_string(std::string asm_string);
        void load_yaml(std::string yaml_file_path);
};