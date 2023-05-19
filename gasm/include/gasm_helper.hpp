#pragma once

#include <string>
#include <vector>
#include <regex>

const std::string WHITESPACE;

std::string ltrim(const std::string &s); // trim left spaces of string
std::string rtrim(const std::string &s); // trim right spaces of string
std::string trim(const std::string &s); // trim left and right spaces of string
std::vector<std::string> split_line(std::string); // split string at spaces ot tabs
std::vector<std::string> splitstr(std::string, std::string); // split string at specified character
std::vector<std::string> asm_string_to_vector(std::string); // splits string at newlines and returns vector of strings
std::vector<std::string> asm_file_path_to_vector(std::string); // opens file at path and returns vector with lines of that file
std::string get_hex_part_from_string(std::string); // get all the valid hex characters from the beginning of a string and convert that to an integer
std::string get_binary_part_from_string(std::string); // get all the valid binary characters from the beginning of a string and convert that to an integer
std::string get_decimal_part_from_string(std::string); // get all the valid decimal characters from the beginning of a string and convert that to an integer