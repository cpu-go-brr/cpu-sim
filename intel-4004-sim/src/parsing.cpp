#include "../include/parsing.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <vector>
#include <algorithm>

/* actual parsing of string
        cases to parse:
            1. Labels and Identifiers
                1.1 Identifiers
                    - match Identifiers and values
                    - extract them
                    - check if they are in vars map
                1.2 Labels
                    - find labels
                    - do as in 1.1
            2. Opcodes and Modifiers
            3. Pragmas
*/

// array of op codes
std::vector<std::string> op_codes = {
    "NOP", "JCN", "FIM", "SRC", "FIN", "JIN", "JUN", "JMS", "INC", "ISZ", "ADD",
    "SUB", "LD", "XCH", "BBL", "LDM", "WRM", "WMP", "WRR", "WR0", "WR1", "WR2",
    "WR3", "SBM", "RDM", "RDR", "ADM", "RD0", "RD1", "RD2", "RD3", "CLB", "CLC",
    "IAC", "CMC", "CMA", "RAL", "RAR", "TCC", "DAC", "TCS", "STC", "DAA", "KBP", "DCL"};

// map of labels defined in the asm code
std::map<std::string, int> labels;

// map of variables defined in the asm code
std::map<std::string, int> vars;

// // count addresses
// int address_count = 0;

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s)
{
    return rtrim(ltrim(s));
}

int string_to_integer(std::string str)
{
    int temp = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] - '0'){

        }
        temp = temp * 10 + (str[i] - '0');
    }
    return temp;
}

std::vector<std::string> split(std::string text)
{
    std::vector<std::string> res{};
    std::regex split_regex("[^\t ]+");
    std::smatch split_matches;

    while (std::regex_search(text, split_matches, split_regex))
    {
        // res.push_back(split_matches[0].str());
        for (auto x : split_matches)
            res.push_back(x);
        text = split_matches.suffix().str();
    }
    return res;
    // std::vector<std::string> words{};
    // std::string delim = " ";

    // std::size_t pos = 0;
    // while (true)
    // {
    //     pos = text.find(delim);
    //     std::cout << pos << "\n";
    //     if(pos != std::string::npos){
    //         words.push_back(trim(text.substr(0, pos)));
    //         text.erase(0, pos + delim.length());
    //     }else{
    //         words.push_back(trim(text.substr(0, pos)));
    //         text.erase(0, pos + delim.length());
    //         break;
    //     }
    // }
    // return words;
}

bool in_array(std::string str, const std::vector<std::string> array)
{
    return std::find(array.begin(), array.end(), str) != array.end();
}

std::vector<int> single_instruction_to_object_code(std::vector<std::string> instruction)
{
    std::vector<std::string> two_word_inst = {"SRC", "FIN", "JIN", "INC", "ADD", "SUB", "LD", "XCH", "BBL", "LDM", "JUN", "JMS"};
    std::vector<std::string> three_word_inst = {"JCN", "FIM", "ISZ"};

    std::map<std::string, int> one_word_inst_map = {
        {"NOP", 0b00000000},
        {"WRM", 0b11100000},
        {"WMP", 0b11100001},
        {"WRR", 0b11100010},
        {"WR0", 0b11100100},
        {"WR1", 0b11100101},
        {"WR2", 0b11100110},
        {"WR3", 0b11100111},
        {"SBM", 0b11101000},
        {"RDM", 0b11101001},
        {"RDR", 0b11101010},
        {"ADM", 0b11101011},
        {"RD0", 0b11101100},
        {"RD1", 0b11101101},
        {"RD2", 0b11101110},
        {"RD3", 0b11101111},
        {"CLB", 0b11110000},
        {"CLC", 0b11110001},
        {"IAC", 0b11110010},
        {"CMC", 0b11110011},
        {"CMA", 0b11110100},
        {"RAL", 0b11110101},
        {"RAR", 0b11110110},
        {"TCC", 0b11110111},
        {"DAC", 0b11111000},
        {"TCS", 0b11111001},
        {"STC", 0b11111010},
        {"DAA", 0b11111011},
        {"KBP", 0b11111100},
        {"DCL", 0b11111101}
    };
    std::string command = instruction[0];
    int first_arg;
    int second_arg;

    if (in_array(command, two_word_inst)){
        std::string tmp_first = instruction[1];

        try{
            first_arg = std::stoi(tmp_first);
        }catch(std::invalid_argument& exc){
            if(vars.find(tmp_first) != vars.end()){
                first_arg = vars[tmp_first];
            }
        }
    }else if (in_array(command, three_word_inst)){
        std::string tmp_first;
        
        if (instruction[1].find(",") != std::string::npos){
            tmp_first = instruction[1].replace(instruction[1].length() - 1, 1, "");
        }else{
            tmp_first = instruction[1];
        }

        try{
            first_arg = std::stoi(tmp_first);
        }catch(std::invalid_argument& exc){
            if(vars.find(tmp_first) != vars.end()){
                first_arg = vars[tmp_first];
            }
        }

        try{
            second_arg = std::stoi(instruction[2]);
        }catch(std::invalid_argument& exc){
            if(vars.find(instruction[2]) != vars.end()){
                second_arg = vars[instruction[2]];
            }
        }
    }

    // std::cout << "first_arg:" << first_arg << "\n";
    // std::cout << "first_arg:" << second_arg << "\n";

    if (command == "JCN")
    {
        return std::vector<int>{(0b0001 << 4) + first_arg % 16, second_arg % 256};
    }
    else if (command == "FIM")
    {
        return std::vector<int>{(0b0010 << 4) + ((first_arg % 8) << 1), second_arg % 256};
    }
    else if (command == "SRC")
    {
        return std::vector<int>{(0b0010 << 4) + ((first_arg % 8) << 1) + 1};
    }
    else if (command == "FIN")
    {
        return std::vector<int>{(0b0011 << 4) + ((first_arg % 8) << 1)};
    }
    else if (command == "JIN")
    {
        return std::vector<int>{(0b0011 << 4) + ((first_arg % 8) << 1) + 1};
    }
    else if (command == "JUN")
    {
        return std::vector<int>{(0b0100 << 4) + ((first_arg % 4096) >> 8), (first_arg % 4096) & 0b11111111};
    }
    else if (command == "JMS")
    {
        return std::vector<int>{(0b0101 << 4) + ((first_arg % 4096) >> 8), (first_arg % 4096) & 0b11111111};
    }
    else if (command == "INC")
    {
        return std::vector<int>{(0b0110 << 4) + (first_arg % 16)};
    }
    else if (command == "ISZ")
    {
        return std::vector<int>{(0b0111 << 4) + (first_arg % 16), second_arg % 256};
    }
    else if (command == "ADD")
    {
        return std::vector<int>{(0b1000 << 4) + (first_arg % 16)};
    }
    else if (command == "SUB")
    {
        return std::vector<int>{(0b1001 << 4) + (first_arg % 16)};
    }
    else if (command == "LD")
    {
        return std::vector<int>{(0b1010 << 4) + (first_arg % 16)};
    }
    else if (command == "XCH")
    {
        return std::vector<int>{(0b1011 << 4) + (first_arg % 16)};
    }
    else if (command == "BBL")
    {
        return std::vector<int>{(0b1100 << 4) + (first_arg % 16)};
    }
    else if (command == "LDM")
    {
        return std::vector<int>{(0b1101 << 4) + (first_arg % 16)};
    }
    else if (one_word_inst_map.find(command) != one_word_inst_map.end()){
        return std::vector<int>{one_word_inst_map[command]};
    }
}

std::vector<std::string> get_clean_instructions(std::string file_path)
{
    std::string asm_instruction;
    std::vector<std::string> cleaned_instructions;

    std::ifstream asm_instruction_file(file_path);

    // read the asm file line by line
    while (getline(asm_instruction_file, asm_instruction))
    {
        if (asm_instruction.find(".END") != std::string::npos ||
            asm_instruction.find("$") != std::string::npos)
        {
            return cleaned_instructions;
        }

        // remove comments from the line
        asm_instruction = asm_instruction.substr(0, asm_instruction.find(";"));

        // regex for variables defined in the asm file
        std::regex rgx_variabels("^([^=*]+)\s*=\s*([^=*]+)$");
        std::smatch matches;

        // std::regex rgx_spaces("^([^=*]+)\s*=\s*([^=*]+)$");

        // apply regex to the current line
        if (std::regex_search(asm_instruction, matches, rgx_variabels))
        {
            std::string var_def = matches[0].str();

            // extract name and variable
            std::string variable_name = trim(var_def.substr(0, var_def.find("=")));
            std::string variable_value = trim(var_def.substr(var_def.find("=") + 1, var_def.size()));

            // insert variable and value into the 'vars' map
            vars.insert({variable_name, std::stoi(variable_value)});
        }
        else if (trim(asm_instruction) != "")
        {
            // if the line isn't empty, append it to the cleaned_instructions list
            cleaned_instructions.push_back(asm_instruction);
        }
    }
    asm_instruction_file.close();
    return cleaned_instructions;
}

std::vector<int> clean_instructions_to_object_code(std::vector<std::string> instructions)
{
    std::vector<int> res;

    for (size_t i = 0; i < instructions.size(); i++)
    {
        std::cout << instructions[i] << "\n";
        std::vector<std::string> split_instruction = split(instructions[i]);

        if (in_array(split_instruction[0], op_codes))
        {
            // switch case with op code and rest
            std::vector<int> tmp = single_instruction_to_object_code(split_instruction);
            for (size_t j = 0; j < tmp.size(); j++)
            {
                res.push_back(tmp[j]);
            }
        }
        else
        {
            // std::cout << split_instruction[0] << "\n";
            /*
             options:
                1. starts with '.' => pragma
                2. 'var = *' => new var that equals current pc
                3. string => new label on current address and op code to bin
                4. '* = num' => pc gets set to num
            */
        }
    }
    return res;
}

void Intel4004Parser::parse(std::string file_path)
{
    std::vector<std::string> cleaned_instructions = get_clean_instructions(file_path);

    std::vector<int> res = clean_instructions_to_object_code(cleaned_instructions);
    std::cout << "\n\n";
    for (size_t i = 0; i < res.size(); i++)
    {
        std::cout << std::hex << res[i] << " ";
        // if (i % 2 != 0){
        //     std::cout << std::hex << res[i] << " ";
        // }else{
        //     std::cout << std::hex << res[i];
        // }
    }
    std::cout << "\n\n\n";
}
