#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "yaml-cpp/yaml.h"

int get_length_of_instruction(std::string inst_name); // get the length of an instruction in bytes
std::string get_code_of_instruction(std::string inst_name); // get the binary representation of an instruction
int parse_value_from_argument(std::string arg, bool allow_lookup_of_other_variables); // parse the value from an argument to a instruction in the assembler code
int parse_key_and_value_from_yaml_entry(YAML::Node key, YAML::Node value, std::vector<std::map<std::string, std::string>> &res); // parse instruction names and their binary representation from the cdf
std::vector<std::map<std::string, std::string>> parse_instruction_codes_from_yaml(std::string yaml_file_path); // parse all instruction names and their binary representation from the cdf
void parse_line_with_variables(std::smatch &matches, int &address_counter); // parse a line where variables are declared in the assembler code
void parse_labels_and_instructions_from_line(std::string &line, int &address_counter, std::vector<std::string> &cleaned_lines); // parse label definition from a line in the assembler code 
void parse_line_with_label(std::vector<std::string> &splitted_line, int &address_counter, std::string &line, std::vector<std::string> &cleaned_lines); // parse line that contains a label
std::vector<std::string> first_iteration(std::vector<std::string> asm_vector); // The first iteration over the assembler code
void set_address_counter(std::smatch &matches, uint &pos, std::vector<int> &res); // setting the value of the address counter to a new value
void insert_byte_from_byte_pragma(std::vector<std::string> &splitted_line, uint &pos, std::vector<int> &res); // apply .BYTE pragma and add a byte to the result vector
void divide_instruction_code_into_segments(std::string &code, std::vector<std::string> &code_segments, std::vector<int> &code_segments_length); // divide binary representation into segments
void get_value_of_current_instruction_with_arguments(std::string &code,
                                                     std::vector<std::string> &code_segments,
                                                     std::vector<int> &code_segments_length,
                                                     std::vector<int> &args,
                                                     int &current_argument,
                                                     int &current_value,
                                                     uint &pos,
                                                     std::vector<int> &res); // get the value of the current instruction with its arguments and add it to the result vector
void append_bytes_of_value_to_result(std::string code, int current_value, uint &pos, std::vector<int> &res); // parse value from string and append value to result vector
void construct_binary_from_splitted_line(std::vector<std::string> &splitted_line, uint &pos, std::vector<int> &res); // converts a splitted line into a vector of bytes
std::vector<int> second_iteration(std::vector<std::string> cleand_lines); // The second iteration over the assembler code

class GenericAssembler{

    public:
        GenericAssembler(){};
        std::vector<int> assemble_file(std::string asm_file_path, std::string yaml_file_path); // assemble file with the file path for the assembler code and the file path for the cdf
        std::vector<int> assemble_file(std::string asm_file_path); // assemble file with the file path for the assembler code
        std::vector<int> assemble_string(std::string asm_string, std::string yaml_file_path); // assemble string with the assembler code and the file path for the cdf
        std::vector<int> assemble_string(std::string asm_string); // assemble string with the assembler code
        void load_yaml(std::string yaml_file_path); // load cdf withput assembling code
}; 