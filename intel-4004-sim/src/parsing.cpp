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
std::map<std::string, uint8_t> labels;

// map of variables defined in the asm code
std::map<std::string, uint8_t> vars;

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

std::string single_instruction_to_object_code(std::vector<std::string> instruction){
    /*
    
    "NOP", "JCN", "FIM", "SRC", "FIN", "JIN", "JUN", "JMS", "INC", "ISZ", "ADD",
    "SUB", "LD", "XCH", "BBL", "LDM", "WRM", "WMP", "WRR", "WR0", "WR1", "WR2",
    "WR3", "SBM", "RDM", "RDR", "ADM", "RD0", "RD1", "RD2", "RD3", "CLB", "CLC",
    "IAC", "CMC", "CMA", "RAL", "RAR", "TCC", "DAC", "TCS", "STC", "DAA", "KBP", "DCL"
    
    else if(instruction[0] == ""){
        
    }

    for (size_t i = 0; i < instruction.size(); i++)
        {
            std::cout << instruction[i] << "\n";
        }

    */
    if (instruction[0] == "NOP"){
        return "00";
    }else if(instruction[0] == "JCN" && instruction.size() == 3){
        std::string first_arg = instruction[1];
        std::string second_arg = instruction[2];
        if (instruction[1].find(",") != std::string::npos)
        {
            first_arg = instruction[1].replace(instruction[1].length()-1, 1, "");
        }

        std::stringstream ss;
        ss << "1";
        ss << std::hex << string_to_integer(first_arg);
        ss << std::hex << string_to_integer(second_arg);

        // std::cout << ss.str();
        return ss.str();
    }else if(instruction[0] == ""){
        
    }
    return "";
}

std::vector<std::string> get_clean_instructions(std::string file_path, bool debug)
{
    std::string asm_instruction;
    std::vector<std::string> cleaned_instructions;

    std::ifstream asm_instruction_file(file_path);

    if (!asm_instruction_file)
    {
        std::cout << "Failed to load file"
                  << "'" << file_path << "'"
                  << "\n";
        // return std::vector<std::string>;
    }

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
            std::string variable_name = var_def.substr(0, var_def.find("="));
            std::string variable_value = var_def.substr(var_def.find("=") + 1, var_def.size());

            // insert variable and value into the 'vars' map
            vars.insert({variable_name, string_to_integer(variable_value)});
        }
        else if (trim(asm_instruction) != "")
        {

            // if the line isn't empty, append it to the cleaned_instructions list
            cleaned_instructions.push_back(asm_instruction);
            //     std::string first_word = split(asm_instruction, " ")[0];
            //     if(in_array(first_word, op_codes)){
            //         labels.insert({first_word, address_count});
            //     }
            //     address_count += 1;
        }
    }
    asm_instruction_file.close();
    return cleaned_instructions;
}

std::string clean_instructions_to_object_code(std::vector<std::string> instructions)
{
    std::string res = "";
    int address_count = 0;

    for (size_t i = 0; i < instructions.size(); i++)
    {
        std::vector<std::string> split_instruction = split(instructions[i]);

        if (in_array(split_instruction[0], op_codes))
        {
            // switch case with op code and rest
            res += single_instruction_to_object_code(split_instruction);
            // std::cout << single_instruction_to_object_code(split_instruction);
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

void Intel4004Parser::parse(std::string file_path, bool debug)
{
    std::vector<std::string> cleaned_instructions = get_clean_instructions(file_path, debug);

    // // print all cleaned instructions
    // for (size_t i = 0; i < cleaned_instructions.size(); i++)
    // {
    //     std::cout << cleaned_instructions[i] << "\n";
    // }

    std::string res = clean_instructions_to_object_code(cleaned_instructions);
    std::cout << "\n\n";
    for (size_t i = 0; i < res.length(); i++)
    {
        if (i % 2 != 0){
            std::cout << res[i] << " ";
        }else{
            std::cout << res[i];
        }
    }
    std::cout << "\n\n\n";
}
