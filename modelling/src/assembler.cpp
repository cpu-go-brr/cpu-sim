#include "../include/assembler.hpp"
#include "yaml-cpp/yaml.h"
#include <vector>
#include <regex>

const std::string WHITESPACE = " \n\r\t\f\v";
std::map<std::string, int> vars;
std::vector<std::map<std::string, std::string>> instruction_codes;

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

std::vector<std::string> split(std::string text)
{
    std::vector<std::string> res{};
    std::regex split_regex("[^\t ]+");
    std::smatch split_matches;

    while (std::regex_search(text, split_matches, split_regex))
    {
        for (auto x : split_matches)
            res.push_back(trim(x));
        text = split_matches.suffix().str();
    }
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

int parse_value_from_argument(std::string arg, bool allow_lookup_of_other_variables = true)
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
    else if ((48 <= arg[0] <= 57))
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
        if (allow_lookup_of_other_variables)
        {
            transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
            if (vars.find(arg) != vars.end())
            {
                return vars[arg];
            }
        }
        else
        {
            std::cout << "ERROR in parse_value_from_argument(): " << exc.what() << "\n";
            return 0;
        }
    }
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
                // std::cout << value_str << " ";

                int value_str_length = (int)value_str.length() / 8;

                while (res.size() < value_str_length)
                {
                    std::map<std::string, std::string> tmp = {};
                    res.push_back(tmp);
                }
                res[value_str_length - 1].insert({key_str, value_str});
            }
            catch (const YAML::TypedBadConversion<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>> e)
            {
                std::cout << "No 'asm' entry in '" << key_str << "' instruction"
                          << "\n";
                return res;
            }
        }
        // std::cout << "\n";
    }
    return res;
}

std::vector<std::string> first_iteration(std::string asm_file_path)
{
    std::string line;
    std::vector<std::string> cleaned_lines;
    int address_counter = 0;

    std::ifstream file(asm_file_path);
    std::regex rgx_variabels("[A-Za-z][A-Za-z0-9_]*[ \t]*=[ \t]*[^ ]+");
    std::regex reg_set_pc("\\*[ \t]*=[ \t]*[^ ]+");

    while (getline(file, line))
    {
        line = line.substr(0, line.find(";"));

        int pos_first_char = line.find_first_not_of(WHITESPACE);
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
        else
        {
            std::vector<std::string> splitted_line = split(line);

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
    file.close();
    return cleaned_lines;
}

std::vector<int> GenercicAssembler::assemble(std::string asm_file_path, std::string yaml_file_path)
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
                            - Mehrere Argumente müssen durch WHITESPACE getrennt sein
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
    std::vector<std::string> cleand_lines = first_iteration(asm_file_path);

    // std::cout << "Instructions:\n";
    // for (size_t i = 0; i < instruction_codes.size(); i++)
    // {
    //     for (auto it = instruction_codes[i].begin(); it != instruction_codes[i].end(); it++)
    //     {
    //         std::cout << it->first << ": " << it->second << "\n";
    //     }
    //     std::cout << "\n";
    // }

    std::cout << "\n#############################################################\n\n";

    // std::cout << "Variables:\n";
    // for (auto it = vars.begin(); it != vars.end(); it++)
    // {
    //     std::cout << std::hex << it->first << ": " << it->second << "\n";
    // }

    std::cout << "\n#############################################################\n\n";

    std::cout << "Cleand lines:\n";
    for (size_t i = 0; i < cleand_lines.size(); i++)
    {
        std::cout << cleand_lines[i] << "\n";
    }

    std::cout << "\n#############################################################\n\n";

    std::vector<std::map<std::string, std::string>> asdf;
    std::vector<int> res = {0xAB, 0xCD};
    return res;
}