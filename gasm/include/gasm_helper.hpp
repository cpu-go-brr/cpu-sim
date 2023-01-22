#pragma once

#include <string>
#include <vector>
#include <regex>

const std::string WHITESPACE;

std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);
std::string trim(const std::string &s);
std::vector<std::string> split_line(std::string);
std::vector<std::string> splitstr(std::string, std::string);
std::vector<std::string> asm_string_to_vector(std::string);
std::vector<std::string> asm_file_path_to_vector(std::string);
std::string get_hex_part_from_string(std::string);
std::string get_binary_part_from_string(std::string);
std::string get_decimal_part_from_string(std::string);