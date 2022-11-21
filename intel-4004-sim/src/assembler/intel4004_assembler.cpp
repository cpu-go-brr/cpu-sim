#include "../../include/assembler/intel4004_assembler.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <vector>
#include <algorithm>
#include <iomanip>

// array of op codes
std::vector<std::string> op_codes = {
    "NOP", "JCN", "FIM", "SRC", "FIN", "JIN", "JUN", "JMS", "INC", "ISZ", "ADD",
    "SUB", "LD", "XCH", "BBL", "LDM", "WRM", "WMP", "WRR", "WR0", "WR1", "WR2",
    "WR3", "SBM", "RDM", "RDR", "ADM", "RD0", "RD1", "RD2", "RD3", "CLB", "CLC",
    "IAC", "CMC", "CMA", "RAL", "RAR", "TCC", "DAC", "TCS", "STC", "DAA", "KBP", "DCL"};

// map of variables defined in the asm code
std::map<std::string, int> vars;

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
    {"DCL", 0b11111101}};

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
        if (str[i] - '0')
        {
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
}

bool in_array(std::string str, const std::vector<std::string> array)
{
    return std::find(array.begin(), array.end(), str) != array.end();
}

int parse_value_from_argument(std::string arg)
{
    if (arg.find(",") != std::string::npos)
    {
        arg = arg.substr(0, arg.find(","));
    }

    int res;
    int base = 10;

    if (arg[0] == '$')
    {
        arg = arg.substr(1, arg.length());
        for (size_t i = 0; i < arg.length(); i++)
        {
            int current_acsii = int(arg[i]);
            if (!(48 <= current_acsii <= 57) && !(65 <= current_acsii <= 70) && !(97 <= current_acsii <= 102))
            {
                arg = arg.substr(0, i);
                break;
            }
        }
        base = 16;
    }
    else if (arg[0] == '%')
    {
        arg = arg.substr(1, arg.length());
        for (size_t i = 0; i < arg.length(); i++)
        {
            int current_acsii = int(arg[i]);
            if (!(48 <= current_acsii <= 49))
            {
                arg = arg.substr(0, i);
                break;
            }
        }
        base = 2;
    }
    else if ((30 <= arg[0] <= 39))
    {
        for (size_t i = 0; i < arg.length(); i++)
        {
            int current_acsii = int(arg[i]);
            if (!(48 <= current_acsii <= 57))
            {
                arg = arg.substr(0, i);
                break;
            }
        }
    }

    try
    {
        return std::stoi(arg, nullptr, base);
    }
    catch (std::invalid_argument &exc)
    {
        if (vars.find(arg) != vars.end())
        {
            return vars[arg];
        }
    }
}

std::vector<int> single_instruction_to_object_code(std::vector<std::string> instruction)
{
    std::string command = instruction[0];
    int first_arg;
    int second_arg;

    if (in_array(command, two_word_inst))
    {
        first_arg = parse_value_from_argument(instruction[1]);
    }
    else if (in_array(command, three_word_inst))
    {
        first_arg = parse_value_from_argument(instruction[1]);
        second_arg = parse_value_from_argument(instruction[2]);
    }

    if (command == "JCN")
    {
        return std::vector<int>{(0b0001 << 4) + (first_arg & 0b1111), (second_arg & 0b11111111)};
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
    else if (one_word_inst_map.find(command) != one_word_inst_map.end())
    {
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
        // remove comments from the line
        asm_instruction = asm_instruction.substr(0, asm_instruction.find(";"));

        int pos_first_char = asm_instruction.find_first_not_of(WHITESPACE);
        if (pos_first_char != std::string::npos && asm_instruction[pos_first_char] == '$')
        {
            return cleaned_instructions;
        }

        if (asm_instruction.find(".END") != std::string::npos)
        {
            return cleaned_instructions;
        }

        // regex for variables defined in the asm file
        std::regex rgx_variabels("^[A-z0-0-_]+\s*=\s*[\$\%]*[0-9]+$");
        std::smatch matches;

        // std::regex rgx_spaces("^([^=*]+)\s*=\s*([^=*]+)$");

        // apply regex to the current line
        if (std::regex_search(asm_instruction, matches, rgx_variabels))
        {
            std::string var_def = matches[0].str();
            // std::cout << var_def << "\n";

            // extract name and variable
            std::string variable_name = trim(var_def.substr(0, var_def.find("=")));
            std::string variable_value = trim(var_def.substr(var_def.find("=") + 1, var_def.size()));

            // insert variable and value into the 'vars' map
            vars.insert({variable_name, parse_value_from_argument(variable_value)});
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

std::vector<std::string> parse_labels(std::vector<std::string> cleaned_instructions)
{
    int address_count = 0;

    std::regex rgx_variabels("^[A-z0-9-]+\s*=\s*[*]$");
    std::regex rgx_pc("^[*]\s*=\s*[\$\%]*[0-9]+$");
    std::smatch matches;
    std::smatch matches2;

    std::vector<std::string> new_instructions = {};

    for (size_t i = 0; i < cleaned_instructions.size(); i++)
    {
        std::string current_line = cleaned_instructions[i];
        std::vector<std::string> split_instruction = split(current_line);
        if (in_array(split_instruction[0], op_codes))
        {
            std::string tmp_inst = split_instruction[0];
            if (tmp_inst == "JCN" || tmp_inst == "FIM" || tmp_inst == "JUN" || tmp_inst == "JMS" || tmp_inst == "ISZ")
            {
                address_count += 2;
            }
            else
            {
                address_count += 1;
            }
            new_instructions.push_back(current_line);
        }
        else if (current_line.find(".BYTE") != std::string::npos)
        {
            address_count += 1;
            new_instructions.push_back(current_line);
        }
        else if (std::regex_search(current_line, matches, rgx_variabels))
        {
            std::string var_def = matches[0].str();

            // std::cout << var_def << "\n";
            std::string variable_name = trim(var_def.substr(0, var_def.find("=")));
            vars.insert({variable_name, address_count});
            // new_instructions.push_back(current_line);
        }
        else if (std::regex_search(current_line, matches2, rgx_pc))
        {
            new_instructions.push_back(current_line);
            // std::cout << current_line << "\n";
        }
        else if (split_instruction[0][0] == '*')
        {
            std::string variable_value = trim(cleaned_instructions[i].substr(cleaned_instructions[i].find("=") + 1, cleaned_instructions[i].size()));
            int variable_value_int = parse_value_from_argument(variable_value);
            address_count = variable_value_int;

            // std::cout << current_line << "\n";
            new_instructions.push_back(current_line);
        }
        else
        {
            // std::cout << split_instruction[0] << "\n";
            vars.insert({split_instruction[0], address_count});
            if (split_instruction.size() > 1)
            {
                std::string tmp_inst = split_instruction[1];
                if (tmp_inst == "JCN" || tmp_inst == "FIM" || tmp_inst == "JUN" || tmp_inst == "JMS" || tmp_inst == "ISZ")
                {
                    address_count += 2;
                }
                else
                {
                    address_count += 1;
                }
                new_instructions.push_back(current_line.substr(current_line.find(split_instruction[1]), current_line.length()));
            }
        }
    }
    return new_instructions;
}

std::vector<int> clean_instructions_to_object_code(std::vector<std::string> cleaned_instructions)
{
    std::vector<int> res{};
    // std::vector<int>::const_iterator position = res.begin();
    int pos = 0;

    for (size_t i = 0; i < cleaned_instructions.size(); i++)
    {
        // std::cout << instructions[i] << "\n";
        std::vector<std::string> split_instruction = split(cleaned_instructions[i]);

        if (in_array(split_instruction[0], op_codes))
        {
            // switch case with op code and rest
            std::vector<int> tmp = single_instruction_to_object_code(split_instruction);
            for (size_t j = 0; j < tmp.size(); j++)
            {
                if (pos >= res.size())
                {
                    res.push_back(tmp[j]);
                }
                else
                {
                    res[pos] = tmp[j];
                }
                pos++;
            }
        }
        else
        {
            // std::cout << split_instruction[0] << "\n";

            if (split_instruction[0] == ".BYTE")
            {
                if (pos >= res.size())
                {
                    res.push_back(parse_value_from_argument(split_instruction[1]));
                }
                else
                {
                    res[pos] = parse_value_from_argument(split_instruction[1]);
                }
                pos++;
                // res.insert(res.begin()+pos, parse_value_from_argument(split_instruction[1]));
            }
            else
            {
                std::string variable_value = trim(cleaned_instructions[i].substr(cleaned_instructions[i].find("=") + 1, cleaned_instructions[i].size()));
                int variable_value_int = parse_value_from_argument(variable_value);
                // std::cout << variable_value << " \n";
                if (variable_value_int > pos)
                {
                    while (pos < variable_value_int)
                    {
                        if (pos >= res.size())
                        {
                            res.push_back(0);
                        }
                        else
                        {
                            res[pos] = 0;
                        }
                        pos++;
                    }
                }
                else
                {
                    pos = variable_value_int;
                }
            }
        }
    }
    return res;
}

std::vector<int> Intel4004Assembler::assemble(std::string file_path)
{
    std::vector<std::string> cleaned_instructions = get_clean_instructions(file_path);
    cleaned_instructions = parse_labels(cleaned_instructions);

    std::vector<int> res = clean_instructions_to_object_code(cleaned_instructions);
    return res;
}
