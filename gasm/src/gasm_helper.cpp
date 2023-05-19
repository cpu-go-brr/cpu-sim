#include <string>
#include <vector>
#include <regex>
#include <fstream>

const std::string WHITESPACE = " \n\r\t\f\v";

// trim left spaces of string
std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

// trim right spaces of string
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

// trim left and right spaces of string
std::string trim(const std::string &s)
{
    return rtrim(ltrim(s));
}

// split string at spaces ot tabs with regex
std::vector<std::string> split_line(std::string text)
{

    std::vector<std::string> res;
    std::regex split_regex("[^\t ]+");
    std::smatch split_matches;

    // search for matching whitespaces in text
    while (std::regex_search(text, split_matches, split_regex))
    {
        // for every match: trim spaces and add it to the result vector
        for (auto x : split_matches)
        {
            res.push_back(trim(x));
        }
        
        // reduce the text
        text = split_matches.suffix().str();
    }
    return res;
}

// split string at specified character
std::vector<std::string> splitstr(std::string str, std::string deli = " ")
{
    std::vector<std::string> res;
    int start = 0;
    int end = str.find(deli);

    // for every found delimiter, add the previous text to the result vector
    while (end != -1)
    {
        // add found substring to vector
        res.push_back(str.substr(start, end - start));
        // calculate new boundaries to search in
        start = end + deli.size();
        end = str.find(deli, start);
    }
    // add last substring to result vector
    res.push_back(str.substr(start, end - start));
    return res;
}

// splits string at newlines and returns vector of strings
std::vector<std::string> asm_string_to_vector(std::string asm_string)
{
    return splitstr(asm_string, "\n");
}

// opens file at path and returns vector with lines of that file
std::vector<std::string> asm_file_path_to_vector(std::string asm_file_path)
{
    std::vector<std::string> res;
    std::string line;
    std::ifstream file(asm_file_path);

    // for every line in the specified file: add the line to the result vector
    while (getline(file, line))
    {
        res.push_back(line);
    }
    file.close();
    return res;
}

// get all the valid hex characters from the beginning of a string and convert that to an integer
std::string get_hex_part_from_string(std::string s)
{
    // for every character in the string
    for (size_t i = 0; i < s.length(); i++)
    {
        // check if the current character is a valid hex character
        // if not return the substring from the beginning to the current position
        int current_ascii = int(s[i]);
        if (!(48 <= current_ascii && current_ascii <= 57) &&
            !(65 <= current_ascii && current_ascii <= 70) &&
            !(97 <= current_ascii && current_ascii <= 102))
        {
            s = s.substr(0, i);
            return s;
        }
    }
    return s;
}

// get all the valid binary characters from the beginning of a string and convert that to an integer
std::string get_binary_part_from_string(std::string s)
{
    // for every character in the string
    for (size_t i = 0; i < s.length(); i++)
    {
        // check if the current character is a valid binary character
        // if not return the substring from the beginning to the current position
        int current_ascii = int(s[i]);
        if (!(48 <= current_ascii && current_ascii <= 49))
        {
            s = s.substr(0, i);
            return s;
        }
    }
    return s;
}

// get all the valid decimal characters from the beginning of a string and convert that to an integer
std::string get_decimal_part_from_string(std::string s)
{
    // for every character in the string
    for (size_t i = 0; i < s.length(); i++)
    {
        // check if the current character is a valid decimal character
        // if not return the substring from the beginning to the current position
        int current_ascii = int(s[i]);
        if (!(48 <= current_ascii && current_ascii <= 57))
        {
            s = s.substr(0, i);
            return s;
        }
    }
    return s;
}
