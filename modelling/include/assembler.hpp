#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class GenercicAssembler{

    public:
        GenercicAssembler(){};
        std::vector<int> assemble(std::string asm_file_path, std::string yaml_file_path);
};