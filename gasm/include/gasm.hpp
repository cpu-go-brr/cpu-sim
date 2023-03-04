#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "yaml-cpp/yaml.h"

int get_length_of_instruction(std::string inst_name);
std::string get_code_of_instruction(std::string inst_name);
int parse_value_from_argument(std::string arg, bool allow_lookup_of_other_variables);
int parse_key_and_value_from_yaml_entry(YAML::Node key, YAML::Node value, std::vector<std::map<std::string, std::string>> &res);
std::vector<std::map<std::string, std::string>> parse_instruction_codes_from_yaml(std::string yaml_file_path);
void parse_line_with_variables(std::smatch &matches, int &address_counter);
void parse_labels_and_instructions_from_line(std::string &line, int &address_counter, std::vector<std::string> &cleaned_lines);
void parse_line_with_label(std::vector<std::string> &splitted_line, int &address_counter, std::string &line, std::vector<std::string> &cleaned_lines);
std::vector<std::string> first_iteration(std::vector<std::string> asm_vector);
void set_pos_to_pc(std::smatch &matches, uint &pos, std::vector<int> &res);
void insert_byte_from_byte_pragma(std::vector<std::string> &splitted_line, uint &pos, std::vector<int> &res);
void divide_instruction_code_into_segments(std::string &code, std::vector<std::string> &code_segments, std::vector<int> &code_segments_length);
void get_value_of_current_instruction_with_arguments(std::string &code,
                                                     std::vector<std::string> &code_segments,
                                                     std::vector<int> &code_segments_length,
                                                     std::vector<int> &args,
                                                     int &current_argument,
                                                     int &current_value,
                                                     uint &pos,
                                                     std::vector<int> &res);
void append_bytes_of_value_to_result(std::string code, int current_value, uint &pos, std::vector<int> &res);
void construct_binary_from_splitted_line(std::vector<std::string> &splitted_line, uint &pos, std::vector<int> &res);
std::vector<int> second_iteration(std::vector<std::string> cleand_lines);

class GenericAssembler{

    public:
        GenericAssembler(){};
        std::vector<int> assemble_file(std::string asm_file_path, std::string yaml_file_path);
        std::vector<int> assemble_file(std::string asm_file_path);
        std::vector<int> assemble_string(std::string asm_string, std::string yaml_file_path);
        std::vector<int> assemble_string(std::string asm_string);
        void load_yaml(std::string yaml_file_path);
};