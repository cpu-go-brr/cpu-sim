#include "../include/gasm.hpp"
#include <vector>
#include <regex>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <cstdint>

const std::string WHITESPACE = " \n\r\t\f\v";
std::map<std::string, int> vars;
std::vector<std::map<std::string, std::string>> instruction_codes = ${INSTRUCTION_CODES}

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

std::vector<std::string> split_line(std::string text)
{
    std::vector<std::string> res;
    std::regex split_regex("[^\t ]+");
    std::smatch split_matches;

    while (std::regex_search(text, split_matches, split_regex))
    {
        for (auto x : split_matches)
        {
            res.push_back(trim(x));
        }
        text = split_matches.suffix().str();
    }
    return res;
}

std::vector<std::string> splitstr(std::string str, std::string deli = " ")
{
    std::vector<std::string> res;
    int start = 0;
    int end = str.find(deli);
    while (end != -1)
    {
        res.push_back(str.substr(start, end - start));
        start = end + deli.size();
        end = str.find(deli, start);
    }
    res.push_back(str.substr(start, end - start));
    return res;
}

int get_length_of_instruction(std::string inst_name)
{
    transform(inst_name.begin(), inst_name.end(), inst_name.begin(), ::tolower);
    for (size_t i = 0; i < instruction_codes.size(); i++)
    {
        if (instruction_codes[i].find(inst_name) != instruction_codes[i].end())
        {
            return i + 1;
        }
    }
    return -1;
}

std::string get_code_of_instruction(std::string inst_name)
{
    transform(inst_name.begin(), inst_name.end(), inst_name.begin(), ::tolower);
    for (size_t i = 0; i < instruction_codes.size(); i++)
    {
        if (instruction_codes[i].find(inst_name) != instruction_codes[i].end())
        {
            return instruction_codes[i][inst_name];
        }
    }
    std::cout << "ERROR in get_code_of_instruction(). No instruction with name '" << inst_name << "'.\n";
    return NULL;
}

int parse_value_from_argument(std::string arg, bool allow_lookup_of_other_variables)
{
    int base = 10;

    if (arg[0] == '$')
    {
        arg = arg.substr(1, arg.length());
        for (size_t i = 0; i < arg.length(); i++)
        {
            int current_ascii = int(arg[i]);
            if (!(48 <= current_ascii && current_ascii <= 57) &&
                !(65 <= current_ascii && current_ascii <= 70) &&
                !(97 <= current_ascii && current_ascii <= 102))
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
            int current_ascii = int(arg[i]);
            if (!(48 <= current_ascii && current_ascii <= 49))
            {
                arg = arg.substr(0, i);
                break;
            }
        }
        base = 2;
    }
    else if ((48 <= arg[0] && arg[0] <= 57))
    {
        for (size_t i = 0; i < arg.length(); i++)
        {
            int current_ascii = int(arg[i]);
            if (!(48 <= current_ascii && current_ascii <= 57))
            {
                arg = arg.substr(0, i);
                break;
            }
        }
    }

    try
    {
        transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
        if (allow_lookup_of_other_variables && vars.find(arg) != vars.end())
        {
            return vars[arg];
        }
        return std::stoi(arg, nullptr, base);
    }
    catch (std::invalid_argument &exc)
    {
        std::stringstream ss;
        ss << "ERROR in parse_value_from_argument(): " << exc.what();
        throw std::invalid_argument(ss.str());
        return 0;
    }
}


std::vector<std::string> asm_string_to_vector(std::string asm_string)
{
    return splitstr(asm_string, "\n");
}

std::vector<std::string> asm_file_path_to_vector(std::string asm_file_path)
{
    std::vector<std::string> res;
    std::string line;
    std::ifstream file(asm_file_path);
    while (getline(file, line))
    {
        res.push_back(line);
    }
    file.close();
    return res;
}

std::vector<std::string> first_iteration(std::vector<std::string> asm_vector)
{
    /*
        This function does the following:
            - parsing all variables and labels from the asm-file
                - variables and labels are being written to the vars-map
            - cleaning up the remaining lines
                - return thes lines
    */
    std::vector<std::string> cleaned_lines;
    int address_counter = 0;

    std::regex rgx_variabels("[A-Za-z][A-Za-z0-9_]*[ \t]*=[ \t]*[^ ]+");
    std::regex reg_set_pc("\\*[ \t]*=[ \t]*[^ ]+");

    for (auto line : asm_vector)
    {
        line = line.substr(0, line.find(";"));

        size_t pos_first_char = line.find_first_not_of(WHITESPACE);
        if (pos_first_char != std::string::npos && line[pos_first_char] == '$')
        {
            return cleaned_lines;
        }

        if (line.find(".END") != std::string::npos)
        {
            return cleaned_lines;
        }

        // parse variables from line
        std::smatch matches;
        if (std::regex_search(line, matches, rgx_variabels))
        {
            std::string var_def = matches[0].str();

            std::string variable_name = trim(var_def.substr(0, var_def.find("=")));
            transform(variable_name.begin(), variable_name.end(), variable_name.begin(), ::tolower);
            std::string variable_value = trim(var_def.substr(var_def.find("=") + 1, var_def.size()));

            // std::cout << "|" << variable_name << "|" << variable_value << "|" << "\n";

            int variable_value_int;
            if (variable_value == "*")
            {
                variable_value_int = address_counter;
            }
            else
            {
                variable_value_int = parse_value_from_argument(variable_value, false);
            }

            if (vars.find(variable_name) == vars.end())
            {
                vars.insert({variable_name, variable_value_int});
            }
            else
            {
                vars[variable_name] = variable_value_int;
            }
        }
        else if (std::regex_search(line, matches, reg_set_pc))
        {
            std::string var_def = matches[0].str();
            std::string variable_value = trim(var_def.substr(var_def.find("=") + 1, var_def.size()));
            address_counter = parse_value_from_argument(variable_value, false);
            cleaned_lines.push_back(line);
        }
        else if (line.find(".BYTE") != std::string::npos)
        {
            cleaned_lines.push_back(trim(line));
            address_counter++;
        }
        else
        {
            std::vector<std::string> splitted_line = split_line(line);

            if (splitted_line.size() >= 1)
            {
                int instruction_length = get_length_of_instruction(splitted_line[0]);
                if (instruction_length == -1)
                {
                    std::string label_name = splitted_line[0];
                    transform(label_name.begin(), label_name.end(), label_name.begin(), ::tolower);
                    if (vars.find(label_name) == vars.end())
                    {
                        vars.insert({label_name, address_counter});
                    }
                    else
                    {
                        vars[label_name] = address_counter;
                    }

                    if (splitted_line.size() >= 2 && get_length_of_instruction(splitted_line[1]) != -1)
                    {
                        address_counter += get_length_of_instruction(splitted_line[1]);
                        std::string new_line = line.substr(line.find(splitted_line[0]) + splitted_line[0].length(), line.length());
                        cleaned_lines.push_back(trim(new_line));
                    }
                }
                else
                {
                    address_counter += get_length_of_instruction(splitted_line[0]);
                    cleaned_lines.push_back(trim(line));
                }
            }
        }
    }
    return cleaned_lines;
}

std::vector<int> second_iteration(std::vector<std::string> cleand_lines)
{
    unsigned int pos = 0;
    std::vector<int> res = {};
    std::regex reg_set_pc("\\*[ \t]*=[ \t]*[^ ]+");

    for (size_t i = 0; i < cleand_lines.size(); i++)
    {
        std::replace(cleand_lines[i].begin(), cleand_lines[i].end(), ',', ' ');
        std::vector<std::string> splitted_line = split_line(cleand_lines[i]);

        std::smatch matches;
        if (std::regex_search(cleand_lines[i], matches, reg_set_pc))
        {
            std::string var_def = matches[0].str();
            std::string variable_value = trim(var_def.substr(var_def.find("=") + 1, var_def.size()));
            unsigned int num = parse_value_from_argument(variable_value, false);

            if (pos < num)
            {
                while (pos < num)
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
                pos = num;
            }
        }
        else if (splitted_line[0] == ".BYTE")
        {
            int val = (parse_value_from_argument(splitted_line[1], true) & 0xff);
            if (pos >= res.size())
            {
                res.push_back(val);
            }
            else
            {
                res[pos] = val;
            }
            pos++;
        }
        else
        {
            // constructing the binary
            std::string code = get_code_of_instruction(splitted_line[0]);
            std::vector<int> args = {};
            for (size_t j = 1; j < splitted_line.size(); j++)
            {
                args.push_back(parse_value_from_argument(splitted_line[j], true));
            }

            std::vector<std::string> code_segments = {};
            std::vector<int> code_segments_length = {};
            std::string tmp_code = "";
            for (size_t j = 0; j < code.length(); j++)
            {
                char last_char = (tmp_code.length() > 0)? tmp_code[tmp_code.length() - 1]:'%'; //why? no one knows

                if (((last_char == '0' || last_char == '1') && (code[j] == '0' || code[j] == '1')) ||
                    (!(last_char == '0' || last_char == '1') && !(code[j] == '0' || code[j] == '1') && last_char == code[j]) ||
                    tmp_code == "")
                {
                    tmp_code += code[j];
                }
                else
                {
                    code_segments.push_back(tmp_code);
                    code_segments_length.push_back(j);
                    tmp_code = code[j];
                }
            }
            code_segments.push_back(tmp_code);
            code_segments_length.push_back(code.length());

            int current_argument = 0;
            int current_value = 0;
            for (size_t j = 0; j < code_segments.size(); j++)
            {
                if (code_segments[j][0] != '0' && code_segments[j][0] != '1' && args.size() >= 1)
                {
                    int argument_value = (args[current_argument] & (int)(pow(2, code_segments[j].length()) - 1));
                    current_value += (argument_value << (code.length() - code_segments_length[j]));
                    current_argument++;
                }
                else
                {
                    current_value += (std::stoi(code_segments[j], nullptr, 2) << (code.length() - code_segments_length[j]));
                }
            }

            for (size_t j = (int)code.length() / 8; j > 0; j--)
            {
                int val = ((current_value >> 8 * (j - 1)) & 0xff);
                if (pos >= res.size())
                {
                    res.push_back(val);
                }
                else
                {
                    res[pos] = val;
                }
                pos++;
            }
        }
    }
    for (size_t i = 0; i < res.size() % 8; i++)
    {
        res.push_back(0);
    }

    return res;
}


std::vector<int> GenericAssembler::assemble_string(std::string asm_string)
{
    if(instruction_codes.empty()){
        return {-1};
    }
    std::vector<std::string> asm_vector = asm_string_to_vector(asm_string);
    std::vector<std::string> cleand_lines = first_iteration(asm_vector);
    std::vector<int> res = second_iteration(cleand_lines);

    return res;
}
