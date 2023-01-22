#include <string>
#include <vector>
#include <regex>
#include <fstream>

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

std::string get_hex_part_from_string(std::string s)
{
    for (size_t i = 0; i < s.length(); i++)
    {
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

std::string get_binary_part_from_string(std::string s)
{
    for (size_t i = 0; i < s.length(); i++)
    {
        int current_ascii = int(s[i]);
        if (!(48 <= current_ascii && current_ascii <= 49))
        {
            s = s.substr(0, i);
            return s;
        }
    }
    return s;
}

std::string get_decimal_part_from_string(std::string s)
{
    for (size_t i = 0; i < s.length(); i++)
    {
        int current_ascii = int(s[i]);
        if (!(48 <= current_ascii && current_ascii <= 57))
        {
            s = s.substr(0, i);
            return s;
        }
    }
    return s;
}
