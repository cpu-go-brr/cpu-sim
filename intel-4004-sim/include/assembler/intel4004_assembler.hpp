#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class Intel4004Assembler{

    public:
        Intel4004Assembler(){};
        std::vector<int> assemble(std::string file_path);
};