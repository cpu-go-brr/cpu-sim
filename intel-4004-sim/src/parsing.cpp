#include "../include/parsing.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <regex>

std::string op_codes[45] = {
    "NOP", "JCN", "FIM", "SRC", "FIN", "JIN", "JUN", "JMS", "INC", "ISZ", "ADD",
    "SUB", "LD", "XCH", "BBL", "LDM", "WRM", "WMP", "WRR", "WR0", "WR1", "WR2",
    "WR3", "SBM", "RDM", "RDR", "ADM", "RD0", "RD1", "RD2", "RD3", "CLB", "CLC",
    "IAC", "CMC", "CMA", "RAL", "RAR", "TCC", "DAC", "TCS", "STC", "DAA", "KBP", "DCL"
};

void Intel4004Parser::parse(std::string file_path, bool debug)
{
    if (debug)
        std::cout << "Parsing..."
                  << "\n";
    std::string asm_instruction;
    std::ifstream asm_instruction_file(file_path);

    if (!asm_instruction_file)
    {
        std::cout << "Failed to load file"
                  << "'" << file_path << "'"
                  << "\n";
        return;
    }

    std::map<std::string, uint8_t> flags;
    std::map<std::string, uint8_t> vars;

    // if (flags.find("flag3") == flags.end())
    //     std::cout << "not in\n";
    // else{
    //     std::cout << "in\n";
    // }

    while (getline(asm_instruction_file, asm_instruction))
    {
        if (debug)
            std::cout << asm_instruction << "\n";

        asm_instruction = asm_instruction.substr(0, asm_instruction.find(";"));

        std::regex rgx("^([^=]+)\s*=\s*([^=]+)$");
        std::smatch matches;

        if(std::regex_search(asm_instruction, matches, rgx)) {
            std::cout << "'" << matches[0].str() << "'\n";
        }

        /* actual parsing of string
        cases to parse:
            1. Labels and Identifiers
                1.1 Identifiers
                    - match Ifentifiers and values
                    - extract them
                    - check if they are in vars map
                1.2 Labels
                    - find labels
                    - do as in 1.1
            2. Opcodes and Modifiers
            3. Pragmas
        */
    }

    asm_instruction_file.close();
}