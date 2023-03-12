#include "../include/gasm.hpp"
#include "yaml-cpp/yaml.h"
#include <vector>
#include <regex>
#include <algorithm>
#include "../include/gasm_helper.hpp"

std::map<std::string, int> vars;
std::vector<std::map<std::string, std::string>> instruction_codes;

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
        arg = get_hex_part_from_string(arg);
        base = 16;
    }
    else if (arg[0] == '%')
    {
        arg = arg.substr(1, arg.length());
        arg = get_binary_part_from_string(arg);
        base = 2;
    }
    else if ((48 <= arg[0] && arg[0] <= 57))
    {
        arg = get_decimal_part_from_string(arg);
    }

    try
    {
        return std::stoi(arg, nullptr, base);
    }
    catch (std::invalid_argument &exc)
    {
        transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
        if (allow_lookup_of_other_variables && vars.find(arg) != vars.end())
        {
            return vars[arg];
        }
        std::stringstream ss;
        ss << "ERROR in parse_value_from_argument(): "
           << "stoi('" << arg << "')";
        throw std::invalid_argument(ss.str());
        return 0;
    }
}

int parse_key_and_value_from_yaml_entry(YAML::Node key, YAML::Node value, std::vector<std::map<std::string, std::string>> &res)
{
    std::string key_str;
    std::string value_str;
    if (key.Type() == YAML::NodeType::Scalar)
    {
        key_str = key.as<std::string>();
        transform(key_str.begin(), key_str.end(), key_str.begin(), ::tolower);

        // std::cout << key_str << ": ";
    }
    if (value.Type() == YAML::NodeType::Map)
    {
        try
        {
            value_str = value["asm"].as<std::string>();
            value_str.erase(std::remove_if(value_str.begin(), value_str.end(), ::isspace), value_str.end());

            if ((int)value_str.length() % 8 != 0)
            {
                value_str.insert(0, 8 - (int)value_str.length() % 8, '0');
            }

            uint value_str_length = (int)value_str.length() / 8;

            while (res.size() < value_str_length)
            {
                std::map<std::string, std::string> tmp = {};
                res.push_back(tmp);
            }
            res[value_str_length - 1].insert({key_str, value_str});
        }
        catch (const YAML::TypedBadConversion<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>> &e)
        {
            std::cout << "ERROR in parse_instruction_codes_from_yaml(). No 'asm' entry in '" << key_str << "' instruction"
                      << "\n";
            return 1;
        }
    }
    return 0;
}

std::vector<std::map<std::string, std::string>> parse_instruction_codes_from_yaml(std::string yaml_file_path)
{
    auto file = YAML::LoadFile(yaml_file_path);
    auto ins = file["instructions"];

    std::vector<std::map<std::string, std::string>> res = {};

    for (auto it = ins.begin(); it != ins.end(); ++it)
    {
        YAML::Node key = it->first;
        YAML::Node value = it->second;
        // std::cout << key.as<std::string>() << "\n";
        // std::cout << "hi" << "\n";

        int return_value = parse_key_and_value_from_yaml_entry(key, value, res);
        if (return_value)
        {
            return res;
        }

        // std::cout << "\n";
    }
    return res;
}

void parse_line_with_variables(std::smatch &matches, int &address_counter)
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

void parse_labels_and_instructions_from_line(std::string &line, int &address_counter, std::vector<std::string> &cleaned_lines)
{
    std::vector<std::string> splitted_line = split_line(line);

    if (splitted_line.size() >= 1)
    {
        int instruction_length = get_length_of_instruction(splitted_line[0]);
        if (instruction_length == -1)
        {
            parse_line_with_label(splitted_line, address_counter, line, cleaned_lines);
        }
        else
        {
            address_counter += get_length_of_instruction(splitted_line[0]);
            cleaned_lines.push_back(trim(line));
        }
    }
}

void parse_line_with_label(std::vector<std::string> &splitted_line, int &address_counter, std::string &line, std::vector<std::string> &cleaned_lines)
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

        std::smatch matches;

        // parse variables from line
        if (std::regex_search(line, matches, rgx_variabels))
        {
            parse_line_with_variables(matches, address_counter);
        }
        // parse setting of pc
        else if (std::regex_search(line, matches, reg_set_pc))
        {
            std::string var_def = matches[0].str();
            std::string variable_value = trim(var_def.substr(var_def.find("=") + 1, var_def.size()));
            address_counter = parse_value_from_argument(variable_value, false);
            cleaned_lines.push_back(line);
        }
        // parse byte pragma
        else if (line.find(".BYTE") != std::string::npos)
        {
            cleaned_lines.push_back(trim(line));
            address_counter++;
        }
        // parse instructions and labels
        else
        {
            parse_labels_and_instructions_from_line(line, address_counter, cleaned_lines);
        }
    }
    return cleaned_lines;
}

void set_pos_to_pc(std::smatch &matches, uint &pos, std::vector<int> &res)
{
    std::string var_def = matches[0].str();
    std::string variable_value = trim(var_def.substr(var_def.find("=") + 1, var_def.size()));
    uint num = parse_value_from_argument(variable_value, false);

    if (pos < num)
    {
        while (pos < num)
        {
            if (pos >= res.size())
            {
                res.push_back(0);
            }
            pos++;
        }
    }
    else
    {
        pos = num;
    }
}

void insert_byte_from_byte_pragma(std::vector<std::string> &splitted_line, uint &pos, std::vector<int> &res)
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

void divide_instruction_code_into_segments(std::string &code, std::vector<std::string> &code_segments, std::vector<int> &code_segments_length)
{
    std::string tmp_code = "";
    for (size_t j = 0; j < code.length(); j++)
    {
        char last_char = tmp_code.length() > 0 ? tmp_code[tmp_code.length() - 1] : '_';
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
}

void get_value_of_current_instruction_with_arguments(std::string &code,
                                                     std::vector<std::string> &code_segments,
                                                     std::vector<int> &code_segments_length,
                                                     std::vector<int> &args,
                                                     int &current_argument,
                                                     int &current_value,
                                                     uint &pos,
                                                     std::vector<int> &res)
{
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
}

void append_bytes_of_value_to_result(std::string code, int current_value, uint &pos, std::vector<int> &res)
{
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

void construct_binary_from_splitted_line(std::vector<std::string> &splitted_line, uint &pos, std::vector<int> &res)
{
    std::string code = get_code_of_instruction(splitted_line[0]);

    // get arguments for instructions in vector
    std::vector<int> args = {};
    for (size_t j = 1; j < splitted_line.size(); j++)
    {
        args.push_back(parse_value_from_argument(splitted_line[j], true));
    }

    // divide instruction code into segments
    std::vector<std::string> code_segments = {};
    std::vector<int> code_segments_length = {};
    divide_instruction_code_into_segments(code, code_segments, code_segments_length);

    uint num_of_arguments_to_take = 0;
    for( auto code_segment: code_segments) {
        if (code_segment[0] != '0' && code_segment[0] != '1') {
            num_of_arguments_to_take++;
        }
    }

    // Error when invalid number of arguments
    if (splitted_line.size() -1 != num_of_arguments_to_take) {
        throw std::invalid_argument("Instruction '" + splitted_line[0] + "' has invalid number of arguments");
    }

    // get total value of current instruction
    int current_argument = 0;
    int current_value = 0;
    get_value_of_current_instruction_with_arguments(code, code_segments, code_segments_length, args, current_argument, current_value, pos, res);

    // append of insert total value of current instruction in res
    append_bytes_of_value_to_result(code, current_value, pos, res);
}

std::vector<int> second_iteration(std::vector<std::string> cleand_lines)
{
    uint pos = 0;
    std::vector<int> res = {};
    std::regex reg_set_pc("\\*[ \t]*=[ \t]*[^ ]+");

    for (size_t i = 0; i < cleand_lines.size(); i++)
    {
        std::replace(cleand_lines[i].begin(), cleand_lines[i].end(), ',', ' ');
        std::vector<std::string> splitted_line = split_line(cleand_lines[i]);

        std::smatch matches;
        // set pos to pc
        if (std::regex_search(cleand_lines[i], matches, reg_set_pc))
        {
            set_pos_to_pc(matches, pos, res);
        }
        // insert byte from byte pragma
        else if (splitted_line[0] == ".BYTE")
        {
            insert_byte_from_byte_pragma(splitted_line, pos, res);
        }
        // constructing the binary
        else
        {
            construct_binary_from_splitted_line(splitted_line, pos, res);
        }
    }

    // padding
    for (size_t i = 0; i < res.size() % 8; i++)
    {
        res.push_back(0);
    }

    return res;
}

std::vector<int> GenericAssembler::assemble_file(std::string asm_file_path, std::string yaml_file_path)
{
    /*
        Notes:
            1. yaml einlesen
                - Funktion, die einen Vector von maps zurückgibt (std::vector<std::map<std::string, std::string>>)
                    - Die map vec[0] repräsentiert die instructions mit 1 Byte Länge
                    - Die map vec[1] repräsentiert die instructions mit 2 Byte Länge
                    - usw.
                    - Eintrag in den maps sieht wie folgt aus:
                        - "JCN": "0001CCCCAAAAAAAA"
                        - "JUN": "0100AAAAAAAAAAAA"
                        - "FIM": "0010RRR0DDDDDDDD"
                        - "JMS": "0101AAAA"
            2. asm einlesen
                - Erstes iterieren:
                    - Kommentare entfernen
                    - Variablen entfernen
                    - Label entfernen
                    - Aktuelle Adresse mitschreiben
                    - Label mit addresse in vars (auf *=NUM achten)
                    - Variablen mit Wert in vars (auf VAR=* achten)
                    - Namen von Labels/Variablen mit Instruction-Namen gegen checken
                        - Generelle regex für Namen von Labels und Variablen: "^[A-Za-z][A-Za-z0-9_]*$"
                        - Groß- / Kleinschreibung ist egal bei Variablen und Labels
                            - START == start == sTaRt
                - Zweites iterieren:
                    - Instruction-Name übersetzen mit Argumenten
                        - Anzahl von Argumenten aus Code parsen
                            - "JCN": "0001CCCCAAAAAAAA" => 2 Argumente C (4-bit) und A (8-bit)
                        - Argumente parsen
                            - Argumente sind so zu formatieren:
                                - hex: $ff
                                - bin: %11111111
                                - dec: 255
                            - Zusätzliche Buchstaben sind nur hinter den Werten erlaubt (alles, was nicht in das Zahlenformat passt, wird ignoriert):
                                - $ffR0 => 255
                                - %00001111P4 => 15
                            - Mehrere Argumente müssen durch WHITESPACE getrennt sein (Komma ist optional)
                                - JCN 12, 34 -> OK
                                - JCN 12 34 -> OK
                                - JCN 12,34 -> NICHT OK
                        - Placeholder (A und C im Code) ersetzen
                    - Auf *=NUM Achten
                        if (NUM > pos){
                            while (pos < NUM){
                                if (pos >= res.size()){
                                    res.push_back(0);
                                }else{
                                    res[pos] = 0;
                                }
                                pos++;
                            }
                        }else{
                            pos = NUM;
                        }
    */

    instruction_codes = parse_instruction_codes_from_yaml(yaml_file_path);
    std::vector<std::string> asm_vector = asm_file_path_to_vector(asm_file_path);
    std::vector<std::string> cleand_lines = first_iteration(asm_vector);
    std::vector<int> res = second_iteration(cleand_lines);

    return res;
}

std::vector<int> GenericAssembler::assemble_file(std::string asm_file_path)
{
    if (instruction_codes.empty())
    {
        return {-1};
    }
    std::vector<std::string> asm_vector = asm_file_path_to_vector(asm_file_path);
    std::vector<std::string> cleand_lines = first_iteration(asm_vector);
    std::vector<int> res = second_iteration(cleand_lines);

    return res;
}

std::vector<int> GenericAssembler::assemble_string(std::string asm_string, std::string yaml_file_path)
{
    instruction_codes = parse_instruction_codes_from_yaml(yaml_file_path);
    std::vector<std::string> asm_vector = asm_string_to_vector(asm_string);
    std::vector<std::string> cleand_lines = first_iteration(asm_vector);
    std::vector<int> res = second_iteration(cleand_lines);

    return res;
}

std::vector<int> GenericAssembler::assemble_string(std::string asm_string)
{
    if (instruction_codes.empty())
    {
        return {-1};
    }
    std::vector<std::string> asm_vector = asm_string_to_vector(asm_string);
    std::vector<std::string> cleand_lines = first_iteration(asm_vector);
    std::vector<int> res = second_iteration(cleand_lines);

    return res;
}

void GenericAssembler::load_yaml(std::string yaml_file_path)
{
    instruction_codes = parse_instruction_codes_from_yaml(yaml_file_path);
}