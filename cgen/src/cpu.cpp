#include "cpu.hpp"
#include "matheval.hpp"
#include <iostream>
#include <assert.h>
#include <regex>
#include <cmath>
#include <cctype>

void CPUDescription::CPU::initInfo(const YAML::Node &config)
{
    name = config["name"].as<std::string>();
    description = config["description"].as<std::string>("");
    display = config["display"].as<std::string>("");
}

void CPUDescription::CPU::initInternalMemory(const YAML::Node &config)
{
    auto mem = config["memory"]["internal"];
    for (YAML::const_iterator it = mem.begin(); it != mem.end(); ++it)
    {
        InternalMemory m(it->first.as<std::string>(), it->second, total_mem);
        total_mem += m.getSize();
        internal_memory.push_back(m);
    }
}

void CPUDescription::CPU::initExternalMemory(const YAML::Node &config)
{
    auto mem = config["memory"]["external"];
    for (YAML::const_iterator it = mem.begin(); it != mem.end(); ++it)
    {
        ExternalMemory m(it->first.as<std::string>(), it->second);
        external_memory.push_back(m);
    }
}

void CPUDescription::CPU::initInstructions(const YAML::Node &config)
{
    auto ins = config["instructions"];
    for (YAML::const_iterator it = ins.begin(); it != ins.end(); ++it)
    {
        Instruction m(it->first.as<std::string>(), it->second);
        instructions.push_back(m);
    }

    fetch = Instruction("fetch", config["fetch"]);
}

CPUDescription::CPU::CPU(std::string path)
{
    auto file = YAML::LoadFile(path);
    initInfo(file);
    initInternalMemory(file);
    initExternalMemory(file);
    initInstructions(file);
}

std::string CPUDescription::CPU::generateHppIncludes()
{
    return "//Autogenerated header for the " + name + "\n"
                                                      "#pragma once\n\n"
                                                      "#include <stdarg.h>\n"
                                                      "#include <stddef.h>\n"
                                                      "#include \"settings.hpp\"\n"
                                                      "#ifndef NO_CPPSTD\n"
                                                      "#include <string>\n"
                                                      "#include <vector>\n\n"
                                                      "#endif\n"
                                                      "#include \"AddressInfo.hpp\"\n"
                                                      "#include \"AddressInfos.hpp\"\n"
                                                      "#include \"bitset.hpp\"\n\n";
}

std::string CPUDescription::CPU::generateHppInstructions()
{
    std::string functions = ""; // the return array
    std::size_t max_bits = 0;   // the maximum number of bits a function has

    for (auto &i : instructions)
    {
        max_bits = std::max(max_bits, i.getSizeOfOPCode()); // set the bitsize to maximum
        functions += "   template <size_t C>\n"             // concatenate declaration of the instruction
                     "   void " +
                     i.getName() + "();\n";
    }
    auto array_size = (unsigned int)std::pow(2, max_bits);                            // calculate space needed o accommodate all instructions
    functions += "\nstatic Intel4004::op ops[" + std::to_string(array_size) + "];\n"; // add array for instruction pointer
    return functions + "\n";
}

std::string CPUDescription::CPU::generateMemory()
{
    // return byte array needed to accommodate all internal memory
    return "   uint8_t memory[" + std::to_string((int)std::ceil(total_mem / 8.0)) + "] = {};\n";
}

std::string CPUDescription::CPU::generateAddressInfos()
{
    std::string ret = "#pragma once\n#include \"AddressInfo.hpp\"\n";

    for (auto m : internal_memory)
        ret += m.getAddressInfo();

    return ret;
}
std::string CPUDescription::CPU::getName()
{
    return name;
}
std::string CPUDescription::CPU::getDescription()
{
    return description;
}
std::string CPUDescription::CPU::getLowerName()
{
    std::string lowername = name;
    std::for_each(lowername.begin(), lowername.end(), [](char &c)
                  { c = std::tolower(c); });

    return lowername;
}

std::string CPUDescription::CPU::generateRunScript()
{
    return "./build.sh\n"
           "./build/" +
           getLowerName();
}
std::string CPUDescription::CPU::generateClass()
{
    std::string c = // class
        "class " + name + "\n"
                          "{\n"
                          "   public:"
                          "   //our internal CPU memory (registers, PC ..)\n" +
        generateMemory() + "\n"
                           "   " +
        name + "();\n\n"
               "   //function pointer\n"
               "   typedef void (" +
        name + "::*op)();\n"
               "\n"
               "void simulate(size_t bytes = 1);\n"
               "char* display();\n"
               "#ifndef NO_CPPSTD\n"
               "std::string json();\n"
               "#endif\n"
               "bitset fetch();\n"
               "bitset get(AddressInfo info);\n"
               "void set(bitset data, AddressInfo info);\n"
               "void set(bitset data, int nums, const AddressInfo* infos);\n"
               "void set(bitset data, bitset& dest);\n";

    for (auto m : external_memory)
        c += m.getInterfaceDeclaration();

    c +=
        "void bin(AddressInfo info, char* addr);\n"
        "void hex(AddressInfo info, char* addr);\n"
        "void dec(AddressInfo info, char* addr);\n"
        "   //functions\n" +
        generateHppInstructions() +
        "char* str = NULL;"
        "};";

    return c;
}

// returns stringsize -1 -3*count('\n')
std::size_t unescapedsize(std::string s)
{
    std::size_t len = s.size() - 1;
    std::smatch m;
    std::regex e("\n"); // matches words beginning by "sub"

    while (std::regex_search(s, m, e))
    {
        len -= 3;
        s = m.suffix().str();
    }
    return len;
}

std::tuple<std::string, std::string> processDisplayInfo(const std::string &display)
{
    std::string params = "", display_str = std::regex_replace(display, std::regex("\\n"), "\\n\\\n"); // escape \n

    std::regex replacements("(0x|0b)?\\{([A-Z][A-Z0-9]+)\\}"); // matchs 0x{PC} 0b{ACC} {R0} ..
    std::smatch sm;
    while (std::regex_search(display_str, sm, replacements))
    {
        std::string prefix = sm[1].str(), address = sm[2].str();
        auto bits = CPUDescription::InternalMemory::address_lengths[address];
        auto characters = bits;
        if (prefix == "")
        {
            characters = (std::size_t)std::ceil(std::log10(std::pow(2, bits)));
            params += "dec";
        }
        else if (prefix == "0x")
        {
            characters = (std::size_t)std::ceil(bits / 4.0);
            params += "hex";
        }
        else if (prefix == "0b")
        {
            params += "bin";
        }
        std::string placeholder = "";
        for (std::size_t i = 0; i < characters; i++)
            placeholder += "X";

        params += "(" + address + ", str +" + std::to_string(unescapedsize(sm.prefix().str())) + ");\n";
        display_str = sm.prefix().str() + placeholder + sm.suffix().str();
    }

    return {display_str, params};
}

std::string CPUDescription::CPU::generateDisplay()
{
    std::string ret, display_str, params;
    std::tie(display_str, params) = processDisplayInfo(display);

    ret += "void " + name + "::bin(AddressInfo info, char* addr)\n{\n\
       get(info).bin(addr);\n\
    }\n";

    ret += "void " + name + "::hex(AddressInfo info, char* addr)\n{\n\
       get(info).hex(addr);\n\
    }\n";

    ret += "void " + name + "::dec(AddressInfo info, char* addr)\n{\n\
       get(info).dec(addr);\n\
    }\n";

    ret += "char* " + name + "::display()\n";
    ret += "{\n";
    ret += "if(str == NULL)\n"
           "{\nstr = (char*)malloc(" +
           std::to_string(unescapedsize(display_str) - 2) + ");\n"
                                                            "sprintf(str, \"" +
           display_str + "\");\n"
                         "}\n";
    ret += params;
    ret += "#ifndef NO_PRINT\n";
    ret += "printf(\"%s\",str);\n";
    ret += "#endif\n";
    ret += "return str;\n";
    ret += "}\n";

    return ret;
}
std::string CPUDescription::CPU::generateCMakeFile()
{
    std::string ret = ""
                      "cmake_minimum_required(VERSION 3.0) # setting this is required\n"
                      "project(" +
                      name + ")            # this sets the project name\n"
                             "file(GLOB_RECURSE sources src/*.cpp include/*.hpp)\n"
                             "add_executable(" +
                      getLowerName() + " ${sources})\n"
                                       "target_compile_options(" +
                      getLowerName() + " PUBLIC -std=c++2a -Wall -Wfloat-conversion)\n"
                                       "target_include_directories(" +
                      getLowerName() + " PUBLIC include)\n"
                                       "install(TARGETS " +
                      getLowerName() + " DESTINATION bin)\n"
                                       "install(DIRECTORY resources DESTINATION bin)\n"
                                       "set(CPACK_PACKAGE_NAME \"" +
                      name + "\")\n"
                             "set(CPACK_PACKAGE_VERSION \"1.0.0\")\n"
                             "set(CPACK_MONOLITHIC_INSTALL 1)\n"
                             "include(CPack)\n";

    return ret;
}

std::string CPUDescription::CPU::generateHpp()
{
    return generateHppIncludes() + generateClass();
}

std::string CPUDescription::CPU::generateCpp()
{
    std::string cpp = generateIncludesCpp();

    cpp += generateInstructionsCpp();

    cpp += generateInstructionJumpTableCpp();
    cpp += generateConstructorCpp();
    cpp += generateDisplay();
    cpp += generateSimulateCpp();
    cpp += generateExternalMemoryCpp();
    cpp += generateFetchCpp();
    cpp += generateMemorySetAndGetCpp();
    cpp += generateJSONCpp();
    return cpp;
}

std::size_t CPUDescription::CPU::getOpCodeMaxLength()
{
    std::size_t max_opcode_size = 0;
    for (auto &i : instructions)
        max_opcode_size = std::max(max_opcode_size, i.getSizeOfOPCode());

    return max_opcode_size;
}

std::map<std::size_t, std::string> CPUDescription::CPU::generateInstructionMap()
{
    std::map<std::size_t, std::string> instruction_map{};
    for (auto &i : instructions)
    {
        //fill instruction map
        for (auto &code : i.getOPCodes())
            instruction_map[std::stoi(code.c_str(), nullptr, 2)] = "&" + name + "::" + i.getName() + "<0b" + code + ">";
    }
    return instruction_map;
}

std::string CPUDescription::CPU::generateInstructionJumpTableCpp()
{    
    auto array_size = (unsigned int)std::pow(2, getOpCodeMaxLength());
    auto instruction_map = generateInstructionMap();
    std::string ret = "Intel4004::op " + name + "::" + "ops[" + std::to_string(array_size) + "] = {\n";

    for (auto i = 0u; i < array_size; i++)
    {
        ret += instruction_map.contains(i)?instruction_map[i]:"NULL";

        if (i != array_size - 1)
            ret += ",\n";
    }

    return ret + "};\n";
}

std::string CPUDescription::CPU::generateInstructionsCpp()
{
    std::string ret = "";
    for (auto i : instructions)
    {
        ret += "/* " + i.getDescription() + "*/\n";
        ret += i.getCode(name) + "\n";
    }
    return ret;
}

std::string CPUDescription::CPU::generateExternalMemoryCpp()
{
    std::string ret = "";
    for (auto &m : external_memory)
        ret += m.getInterfaceCode(name);

    return ret;
}

std::string CPUDescription::CPU::generateIncludesCpp()
{
    return "#include \"" + name + ".hpp\"\n"
                                  "#include <stdio.h>\n"
                                  "#include <stdlib.h>\n";
}
std::string CPUDescription::CPU::generateConstructorCpp()
{
    std::string ret = name + "::" + name + "()\n{\n";
    for (auto &m : external_memory)
    {
        ret += m.getInitCode();
    }
    return ret + "\n}\n";
}

std::string CPUDescription::CPU::generateSimulateCpp()
{
    return "void " + name + "::simulate(size_t i)\n{\n"
                            "for (;i-->0;)\n"
                            "{\n"
                            "   auto val = fetch();\n"
                            "   if(ops[val.val()] == NULL)\n"
                            "   {\n"
                            "   #ifndef NO_PRINT\n"
                            "   fprintf(stderr, \"%zx unknown\\n\", val.val());\n"
                            "   #endif\n"
                            "   break;\n"
                            "   }\n"
                            "   (this->*ops[val.val()])();\n"
                            "}\n"
                            "}\n";
}
std::string CPUDescription::CPU::generateFetchCpp()
{
    return "bitset " + name + "::fetch()\n"
                              "{\n" +
           fetch.generateFunction(name) +
           "}\n";
}

std::string CPUDescription::CPU::generateMemorySetAndGetCpp()
{
    return "void " + name + "::set(bitset data, AddressInfo info)\n{\nset_mem(&memory[0], info, data);\n}\n"
    "void " + name + "::set(bitset data, bitset& dest)\n{\ndest=bitset(data,dest.size());\n}\n"
    "void " + name + "::set(bitset data, int num, const AddressInfo* infos)\n{\n"
                     "for(size_t i = num; i --> 0;)\n"
                     "{\n"
                     "set_mem(&memory[0], infos[i], data);\n"
                     "data = data >> infos[i].length;\n"
                     "}\n}\n"
    "bitset " + name + "::get(AddressInfo info)\n"
                       "{\n"
                       "   return get_mem(&memory[0], info);\n"
                       "}\n";
}
std::string CPUDescription::CPU::generateJSONCpp()
{
    std::string ret = "#ifndef NO_CPPSTD\n"
                      "    std::string Intel4004::json()\n"
                      "{\n"
                      "std::string json = \"{\\\"internal\\\":{\"\n";
    for (auto m : internal_memory)
        ret += m.getJSONDescription() + "\n";

    ret = ret.substr(0, ret.size() - 3) + "},\\\"external\\\":{\"\n";
    for (auto m : external_memory)
    {
        ret += "\"\\\"" + m.getName() + "\\\":{\\\"bits\\\":" + std::to_string(m.getBits()) + ",\\\"vals\\\":[\";\n";
        ret += "for(size_t i = 0; i < " + std::to_string(m.getWords()) + "; i++) json += std::to_string(" + m.getName() + "_mem[i].val()) + \",\";\n"
                                                                                                                          "json = json.substr(0,json.size()-1);\n";
        ret += "json += \"]},\";\njson +=";
    }
    ret = ret.substr(0, ret.size() - 12) + "\"\n\"}}\";\n";
    ret += "return json + \"}\";\n}\n#endif\n";

    return ret;
}
