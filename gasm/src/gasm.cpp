#include "../include/gasm.hpp"
#include "yaml-cpp/yaml.h"
#include <vector>
#include <regex>
#include <algorithm>
#include "../include/gasm_helper.hpp"

std::map<std::string, int> vars; // map of variables and labels and their values
std::vector<std::map<std::string, std::string>> instruction_codes; // mapping of instruction code and their binary representation sorted by size in bytes

// get the length of an instruction in bytes
int get_length_of_instruction(std::string inst_name)
{
    // convert instruction name to lowercase
    transform(inst_name.begin(), inst_name.end(), inst_name.begin(), ::tolower);

    // search for instructions and return index in the instruction_codes vector + 1 to get length in bytes
    for (size_t i = 0; i < instruction_codes.size(); i++)
    {
        if (instruction_codes[i].find(inst_name) != instruction_codes[i].end())
        {
            return i + 1;
        }
    }

    // return -1 when instruction can't be found
    return -1;
}

// get the binary representation of an instruction
std::string get_code_of_instruction(std::string inst_name)
{
    // convert instruction name to lowercase
    transform(inst_name.begin(), inst_name.end(), inst_name.begin(), ::tolower);

    // search for instructions and return the binary representation of the instruction
    for (size_t i = 0; i < instruction_codes.size(); i++)
    {
        if (instruction_codes[i].find(inst_name) != instruction_codes[i].end())
        {
            return instruction_codes[i][inst_name];
        }
    }
    std::cout << "ERROR in get_code_of_instruction(). No instruction with name '" << inst_name << "'.\n";

    // return NULL when instruction can't be found
    return NULL;
}

// parse the value from an argument to a instruction in the assembler code
int parse_value_from_argument(std::string arg, bool allow_lookup_of_other_variables)
{
    int base = 10;

    // parse value as hexadecimal
    if (arg[0] == '$')
    {
        arg = arg.substr(1, arg.length());
        arg = get_hex_part_from_string(arg);
        base = 16;
    }
    // parse value as binary
    else if (arg[0] == '%')
    {
        arg = arg.substr(1, arg.length());
        arg = get_binary_part_from_string(arg);
        base = 2;
    }
    // parse value as decimal
    else if ((48 <= arg[0] && arg[0] <= 57))
    {
        arg = get_decimal_part_from_string(arg);
    }

    // try to convert substring with specified base to an integer
    try
    {
        return std::stoi(arg, nullptr, base);
    }
    // if it fails, try to look up the substring in the variables
    catch (std::invalid_argument &exc)
    {

        // convert argument to lowercase
        transform(arg.begin(), arg.end(), arg.begin(), ::tolower);

        // search for argument in variables and return the values
        if (allow_lookup_of_other_variables && vars.find(arg) != vars.end())
        {
            return vars[arg];
        }

        // print error and throw std::invalid_argument
        std::stringstream ss;
        ss << "ERROR in parse_value_from_argument(): "
           << "stoi('" << arg << "')";
        throw std::invalid_argument(ss.str());
        return 0;
    }
}

// parse an instruction name and their binary representation from a entry in a yaml
int parse_key_and_value_from_yaml_entry(YAML::Node key, YAML::Node value, std::vector<std::map<std::string, std::string>> &res)
{
    std::string key_str;
    std::string value_str;
    if (key.Type() == YAML::NodeType::Scalar)
    {
        // convert instruction name to lowercase
        key_str = key.as<std::string>();
        transform(key_str.begin(), key_str.end(), key_str.begin(), ::tolower);
    }
    if (value.Type() == YAML::NodeType::Map)
    {
        // try to get the value of the 'asm' key (binary representation of the instruction)
        try
        {
            // get binary representation
            value_str = value["asm"].as<std::string>();
            // remove spaces
            value_str.erase(std::remove_if(value_str.begin(), value_str.end(), ::isspace), value_str.end());

            // pad binary to full bytes
            if ((int)value_str.length() % 8 != 0)
            {
                value_str.insert(0, 8 - (int)value_str.length() % 8, '0');
            }

            // calculate length of the instruction in bytes
            uint value_str_length = (int)value_str.length() / 8;

            // add empty maps for yet missing instructions
            while (res.size() < value_str_length)
            {
                std::map<std::string, std::string> tmp = {};
                res.push_back(tmp);
            }
            // add current instruction with their binary representation to the result vector
            res[value_str_length - 1].insert({key_str, value_str});
        }
        // print error if 'asm' key cant be found in current instruction
        catch (const YAML::TypedBadConversion<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>> &e)
        {
            std::cout << "ERROR in parse_instruction_codes_from_yaml(). No 'asm' entry in '" << key_str << "' instruction"
                      << "\n";
            return 1;
        }
    }
    return 0;
}

// parse all instruction names and their binary representation from the cdf
std::vector<std::map<std::string, std::string>> parse_instruction_codes_from_yaml(std::string yaml_file_path)
{
    // load file and get the section of the instructions
    auto file = YAML::LoadFile(yaml_file_path);
    auto ins = file["instructions"];

    std::vector<std::map<std::string, std::string>> res = {};

    // for every instruction, parse their binary representation
    for (auto it = ins.begin(); it != ins.end(); ++it)
    {
        // set key and value to the current instruction
        YAML::Node key = it->first;
        YAML::Node value = it->second;

        // parse the instruction name and the binary representation
        int return_value = parse_key_and_value_from_yaml_entry(key, value, res);
        if (return_value)
        {
            return res;
        }
    }
    return res;
}

// parse a line where variables are declared in the assembler code
void parse_line_with_variables(std::smatch &matches, int &address_counter)
{
    std::string var_def = matches[0].str();

    // get name and value of the variable
    std::string variable_name = trim(var_def.substr(0, var_def.find("=")));
    transform(variable_name.begin(), variable_name.end(), variable_name.begin(), ::tolower);
    std::string variable_value = trim(var_def.substr(var_def.find("=") + 1, var_def.size()));

    int variable_value_int;

    // set value to current address
    if (variable_value == "*")
    {
        variable_value_int = address_counter;
    }
    // parse integer value from the argument
    else
    {
        variable_value_int = parse_value_from_argument(variable_value, false);
    }
    

    // add new variable
    if (vars.find(variable_name) == vars.end())
    {
        vars.insert({variable_name, variable_value_int});
    }
    // redefine value of variable (variable already exists)
    else
    {
        vars[variable_name] = variable_value_int;
    }
}

// parse label definition from a line in the assembler code 
void parse_labels_and_instructions_from_line(std::string &line, int &address_counter, std::vector<std::string> &cleaned_lines)
{
    std::vector<std::string> splitted_line = split_line(line);

    // if there are more than one words separated with space in the line --> has to be instruction in that line
    if (splitted_line.size() >= 1)
    {
        int instruction_length = get_length_of_instruction(splitted_line[0]);
        // test if first word is the instruction. If not parse the label
        if (instruction_length == -1)
        {
            parse_line_with_label(splitted_line, address_counter, line, cleaned_lines);
        }
        // add line to processed lines and add to address counter
        else
        {
            address_counter += get_length_of_instruction(splitted_line[0]);
            cleaned_lines.push_back(trim(line));
        }
    }
}

// parse line that contains a label
void parse_line_with_label(std::vector<std::string> &splitted_line, int &address_counter, std::string &line, std::vector<std::string> &cleaned_lines)
{
    // get label name
    std::string label_name = splitted_line[0];
    // convert label name to lowercase
    transform(label_name.begin(), label_name.end(), label_name.begin(), ::tolower);

    // label is not known
    if (vars.find(label_name) == vars.end())
    {
        vars.insert({label_name, address_counter});
    }
    // label if known
    else
    {
        vars[label_name] = address_counter;
    }

    // test if an instruction is behind the label and add that line to the processed lines
    if (splitted_line.size() >= 2 && get_length_of_instruction(splitted_line[1]) != -1)
    {
        // get length of the instructions and add that to the address counter
        address_counter += get_length_of_instruction(splitted_line[1]);
        // remove label from line
        std::string new_line = line.substr(line.find(splitted_line[0]) + splitted_line[0].length(), line.length());
        // add line to the processed lines
        cleaned_lines.push_back(trim(new_line));
    }
}

// The first iteration over the assembler code
std::vector<std::string> first_iteration(std::vector<std::string> asm_vector)
{
    /*
        This function does the following:
            - parsing all variables and labels from the asm-file
                - variables and labels are being written to the vars-map
                - lines containing variables or just labels are being removed
            - cleaning up the remaining lines
            - return the lines
    */

    // vector of strings for processed lines
    std::vector<std::string> cleaned_lines;
    // start address counter at 0
    int address_counter = 0;

    // regular expressions to detect variables and the setting of the program counter
    std::regex rgx_variabels("[A-Za-z][A-Za-z0-9_]*[ \t]*=[ \t]*[^ ]+");
    std::regex reg_set_pc("\\*[ \t]*=[ \t]*[^ ]+");

    // iterate over every line
    for (auto line : asm_vector)
    {
        // remove comments from code
        line = line.substr(0, line.find(";"));

        // check if parsing should be aborted ($ as first non-whitespace character in a line)
        size_t pos_first_char = line.find_first_not_of(WHITESPACE);
        if (pos_first_char != std::string::npos && line[pos_first_char] == '$')
        {
            return cleaned_lines;
        }

        // check if parsing should be aborted (.END pragma)
        if (line.find(".END") != std::string::npos)
        {
            return cleaned_lines;
        }

        std::smatch matches;

        // parse variables from the current line
        if (std::regex_search(line, matches, rgx_variabels))
        {
            parse_line_with_variables(matches, address_counter);
        }

        // parse the setting of the program counter
        else if (std::regex_search(line, matches, reg_set_pc))
        {
            std::string var_def = matches[0].str();
            // get new value of program counter
            std::string variable_value = trim(var_def.substr(var_def.find("=") + 1, var_def.size()));
            // set new value
            address_counter = parse_value_from_argument(variable_value, false);
            // add line to processed lines
            cleaned_lines.push_back(line);
        }
        // parse the .BYTE pragma
        else if (line.find(".BYTE") != std::string::npos)
        {
            // add line to processed lines
            cleaned_lines.push_back(trim(line));
            // adjust the address counter
            address_counter++;
        }
        // parse instructions and labels from line
        else
        {
            parse_labels_and_instructions_from_line(line, address_counter, cleaned_lines);
        }
    }
    return cleaned_lines;
}

// setting the value of the address counter to a new value
void set_address_counter(std::smatch &matches, uint &pos, std::vector<int> &res)
{   
    // get value
    std::string var_def = matches[0].str();
    std::string variable_value = trim(var_def.substr(var_def.find("=") + 1, var_def.size()));
    uint num = parse_value_from_argument(variable_value, false);

    // new value is bigger than the address counter
    if (pos < num)
    {
        while (pos < num)
        {
            // if current value of the address counter is bigger then the length of the result vector
            if (pos >= res.size())
            {
                // append zeros the the result vector
                res.push_back(0);
            }
            // add one to the value of the address counter
            pos++;
        }
    }
    // new value is smaller than the address counter
    else
    {
        pos = num;
    }
}

// apply .BYTE pragma and add a byte to the result vector
void insert_byte_from_byte_pragma(std::vector<std::string> &splitted_line, uint &pos, std::vector<int> &res)
{
    // get value of byte
    int val = (parse_value_from_argument(splitted_line[1], true) & 0xff);

    // if current value of the address counter if bigger then the length of the result vector
    if (pos >= res.size())
    {
        // append byte to result vector
        res.push_back(val);
    }
    else
    {
        // write byte at the current position of the address counter in the result vector
        res[pos] = val;
    }
    pos++;
}

/*
divide binary representation into segments
    e.g. 0100CCCAAAAAAAA is being divided into the following segments:
    0100 CCCC AAAAAAAA
*/
void divide_instruction_code_into_segments(std::string &code, std::vector<std::string> &code_segments, std::vector<int> &code_segments_length)
{
    // temporary code segment
    std::string tmp_code = "";

    // iterate over every character in the binary representation
    for (size_t j = 0; j < code.length(); j++)
    {
        // get last character of the temporary code segment
        char last_char = tmp_code.length() > 0 ? tmp_code[tmp_code.length() - 1] : '_';

        // if the last character is a 0 or 1 and the current character is also a 1 or 0 OR
        //    the last character is not a 1 or 0 and the current character is also not a 1 or 0 and both characters are equal OR
        //    the temporary code segment is empty
        if (((last_char == '0' || last_char == '1') && (code[j] == '0' || code[j] == '1')) ||
            (!(last_char == '0' || last_char == '1') && !(code[j] == '0' || code[j] == '1') && last_char == code[j]) ||
            tmp_code == "")
        {
            // add the current character to the temporary code segment
            tmp_code += code[j];
        }
        else
        {
            // add the current segment and its length to the vectors
            code_segments.push_back(tmp_code);
            code_segments_length.push_back(j);
            // reset the temporary code segment
            tmp_code = code[j];
        }
    }
    // add the remaining segment and its length to the vectors
    code_segments.push_back(tmp_code);
    code_segments_length.push_back(code.length());
}

// get the value of the current instruction with its arguments and add it to the result vector
void get_value_of_current_instruction_with_arguments(std::string &code,
                                                     std::vector<std::string> &code_segments,
                                                     std::vector<int> &code_segments_length,
                                                     std::vector<int> &args,
                                                     int &current_argument,
                                                     int &current_value,
                                                     uint &pos,
                                                     std::vector<int> &res)
{
    // iterate over the code segments
    for (size_t j = 0; j < code_segments.size(); j++)
    {
        // if current code segment is a placeholder like 'CCCC' and there is at least one argument
        if (code_segments[j][0] != '0' && code_segments[j][0] != '1' && args.size() >= 1)
        {
            // the value of the argument (get only the bits that fall into the length of the placeholder)
            int argument_value = (args[current_argument] & (int)(pow(2, code_segments[j].length()) - 1));

            // shift the value of the argument to the position in the code segments so the real size is correct
            current_value += (argument_value << (code.length() - code_segments_length[j]));

            // count the argument
            current_argument++;
        }
        else
        {
            // convert the string to an integer and shift the value to the position in the code segments so the real size is correct
            current_value += (std::stoi(code_segments[j], nullptr, 2) << (code.length() - code_segments_length[j]));
        }
    }
}

// parse value from string and append value to result vector
void append_bytes_of_value_to_result(std::string code, int current_value, uint &pos, std::vector<int> &res)
{
    // iterate over all the bytes in the code
    for (size_t j = (int)code.length() / 8; j > 0; j--)
    {
        // calculate value (shift the current value accordingly)
        int val = ((current_value >> 8 * (j - 1)) & 0xff);

        // add value to the result vector
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

// converts a splitted line into a vector of bytes
void construct_binary_from_splitted_line(std::vector<std::string> &splitted_line, uint &pos, std::vector<int> &res)
{
    // get the code of the instruction
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

    // count the number of arguments in the code segments
    uint num_of_arguments_to_take = 0;
    for( auto code_segment: code_segments) {
        if (code_segment[0] != '0' && code_segment[0] != '1') {
            num_of_arguments_to_take++;
        }
    }

    // throw error when invalid number of arguments
    if (splitted_line.size() -1 != num_of_arguments_to_take) {
        throw std::invalid_argument("Instruction '" + splitted_line[0] + "' has invalid number of arguments");
    }

    // get total value of current instruction
    int current_argument = 0;
    int current_value = 0;
    get_value_of_current_instruction_with_arguments(code, code_segments, code_segments_length, args, current_argument, current_value, pos, res);

    // append or insert total value of current instruction in the result vector
    append_bytes_of_value_to_result(code, current_value, pos, res);
}

// The second iteration over the assembler code
std::vector<int> second_iteration(std::vector<std::string> cleand_lines)
{
    /*
        This function does one of the following for every line:
            - set the address counter to a certain values
            - insert a byte from the .BYTE pragma
            - convert the line to binary
    */

    uint pos = 0;
    std::vector<int> res = {};
    std::regex reg_set_pc("\\*[ \t]*=[ \t]*[^ ]+");

    for (size_t i = 0; i < cleand_lines.size(); i++)
    {
        // replace ',' with space in the line
        std::replace(cleand_lines[i].begin(), cleand_lines[i].end(), ',', ' ');

        // split the line at spaces
        std::vector<std::string> splitted_line = split_line(cleand_lines[i]);

        std::smatch matches;
        // check if address counter has to be set
        if (std::regex_search(cleand_lines[i], matches, reg_set_pc))
        {
            //set address counter to current position
            set_address_counter(matches, pos, res);
        }
        // insert a byte from the .BYTE pragma
        else if (splitted_line[0] == ".BYTE")
        {
            insert_byte_from_byte_pragma(splitted_line, pos, res);
        }
        // construct the binary and add it to the result vector
        else
        {
            construct_binary_from_splitted_line(splitted_line, pos, res);
        }
    }

    // add padding to the result vector for its length to be divisible by 8
    for (size_t i = 0; i < res.size() % 8; i++)
    {
        res.push_back(0);
    }

    return res;
}

// assemble file with the file path for the assembler code and the file path for the cdf
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

// assemble file with the file path for the assembler code
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

// assemble string with the assembler code and the file path for the cdf
std::vector<int> GenericAssembler::assemble_string(std::string asm_string, std::string yaml_file_path)
{
    instruction_codes = parse_instruction_codes_from_yaml(yaml_file_path);
    std::vector<std::string> asm_vector = asm_string_to_vector(asm_string);
    std::vector<std::string> cleand_lines = first_iteration(asm_vector);
    std::vector<int> res = second_iteration(cleand_lines);

    return res;
}

// assemble string with the assembler code
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

// load cdf withput assembling code
void GenericAssembler::load_yaml(std::string yaml_file_path)
{
    instruction_codes = parse_instruction_codes_from_yaml(yaml_file_path);
}