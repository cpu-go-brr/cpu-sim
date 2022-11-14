#include "cpu.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cmath>

std::string Description::CPU::generateHeader()
{
    std::string header =
        "//Autogenerated header for the " + name + "\n"
                                                   "#pragma once\n\n"
                                                   "#include <string>\n"
                                                   "#include <map>\n"
                                                   "#include <vector>\n\n"
                                                   "#include \"AddressInfo.hpp\"\n"
                                                   "#include \"AddressInfos.hpp\"\n"
                                                   "#include \"bitset.hpp\"\n\n";

    return header;
}

std::string Description::CPU::generateFunctions()
{
    std::string functions = "";
    // std::string map =
    //     "   std::map<std::size_t, Intel4004::op> ops = \n"
    //     "   {\n";

    functions += "   bitset get(AddressInfo info);\n";
    functions += "   void set(AddressInfo info, bitset data);\n";

    //TODO: add function
    functions += "   void set(std::vector<AddressInfo> infos, bitset data);\n";
    functions += "   void set(bitset& dest, bitset data);\n";

    for (auto &i : instructions)
    {
        functions += "   template <std::size_t C>\n";
        functions += "   void " + i.name + "();\n";

        // for (auto code : i.getOPCodes())
        //     map += "      {0b" + code + ", &" + name + "::" + i.name + "<0b" + code + ">},\n";
    }

    // map += "   };\n";
    return functions + "\n"; // + map;
}
std::string Description::CPU::generateMemory()
{
    std::string ret = "   uint8_t memory[" +
                      std::to_string((int)std::ceil(total_mem / 8.0)) + "] = {};\n";

    return ret;
}

std::string getMemoryNames(Description::InternalMemory m)
{
    std::string ret = "";
    ret += m.name + ",";
    for (auto mem : m.submemory)
        ret += getMemoryNames(mem);

    return ret;
}


std::string describeMemory(Description::InternalMemory m)
{
    std::string ret = "const AddressInfo " + m.name + "{" + std::to_string(m.byteoffset) + ", " + std::to_string(m.bitoffset) + ", " + std::to_string(m.size) + "};\n";
    for (auto mem : m.submemory)
        ret += describeMemory(mem);

    return ret;
}

std::string Description::CPU::generateAddressInfos()
{
    std::string ret = "#pragma once\n#include \"AddressInfo.hpp\"\n";

    for (auto m : internal_memory)
    {
        ret += describeMemory(m);
        ret += "\n\n";
    }

    return ret;
}

std::string Description::CPU::generateClass()
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
               "void simulate(std::size_t bytes = 1);\n"
               "void display();\n"
               "bitset fetch();\n";

        for(auto m: external_memory)
        c += m.getDeclaration();
        
            //    "bitset rom(bitset val);\n"
            //    "uint8_t* ram(bitset val);\n"
            c +=
               "std::string bin(AddressInfo info);\n"
               "std::string hex(AddressInfo info);\n"
               "std::string dec(AddressInfo info);\n"
               "   //functions\n" +
        generateFunctions() +
        "\nstd::map<std::size_t, Intel4004::op> ops;\n"
        "};";

    return c;
}

std::string Description::CPU::generateMainFile()
{
    std::string ret = "#include \"" + name + ".hpp\"\n";

    ret += "int main (int argc, char** argv)\n";
    ret += "{\n";
    ret += name + " cpu;\n";
    ret += "return 0;\n";
    ret += "}\n";

    return ret;
}

std::string Description::CPU::generateDisplay()
{

    // replace our display:
    // binary

    auto display_str = display;
    std::regex bin("0b\\{([\\w]+)\\}");
    std::regex hex("0x\\{([\\w]+)\\}");
    std::regex dec("\\{([\\w]+)\\}");
    std::smatch sm;

    display_str = std::regex_replace(display_str, bin, "\" + bin( $1 ) + \"");
    display_str = std::regex_replace(display_str, hex, "\" + hex( $1 ) + \"");
    display_str = std::regex_replace(display_str, dec, "\" + dec( $1 ) + \"");

    std::string ret;

    ret += "std::string " + name + "::bin(AddressInfo info)\n{\n\
       return get(info).bin();\n\
    }\n";

    ret += "std::string " + name + "::hex(AddressInfo info)\n{\n\
       return get(info).hex();\n\
    }\n";

    ret += "std::string " + name + "::dec(AddressInfo info)\n{\n\
       return get(info).dec();\n\
    }\n";

    ret += "void " + name + "::display()\n{\n";
    ret += "std::string format = " + display_str + ";\n";
    ret += "std::cout << format;\n";
    ret += "}\n";

    return ret;
}
std::string Description::CPU::generateCMakeFile()
{
    std::string ret = "  "
                      "cmake_minimum_required(VERSION 3.0) # setting this is required\n"
                      "project(" +
                      name + ")            # this sets the project name\n"
                             "file(GLOB_RECURSE sources src/*.cpp include/*.hpp)\n"
                             "add_executable(simulator ${sources})\n"
                             "target_compile_options(simulator PUBLIC -std=c++2a -Wall -Wfloat-conversion)\n"
                             "target_include_directories(simulator PUBLIC include)\n"
                             "install(TARGETS simulator DESTINATION bin)\n"
                             "install(DIRECTORY resources DESTINATION bin)\n"
                             "set(CPACK_PACKAGE_NAME \"" +
                      name + "\")\n"
                             "set(CPACK_PACKAGE_VERSION \"1.0.0\")\n"
                             "set(CPACK_MONOLITHIC_INSTALL 1)\n"
                             "include(CPack)\n";

    return ret;
}

void Description::CPU::generate()
{

    std::filesystem::copy("resources/", "out/", std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);

    std::filesystem::create_directory("out");
    std::ofstream hpp("out/include/" + name + ".hpp", std::ios::trunc);

    hpp << generateHeader();
    hpp << generateClass();
    hpp.close();

    std::ofstream info("out/include/AddressInfos.hpp", std::ios::trunc);
    info << generateAddressInfos();
    info.close();

    std::ofstream cpp("out/src/" + name + ".cpp", std::ios::trunc);
    cpp << "#include \"" + name + ".hpp\"\n";

    cpp << "bitset " + name + "::get(AddressInfo info)\n"
                              "{\n"
                              "   return get_mem(&memory[0], info);\n"
                              "}\n";
    for (auto i : instructions)
    {
        cpp << "/* " << i.description << "*/\n";
        cpp << i.getFunction(name) << "\n";
    }

    cpp << name + "::" + name + "()\n{\n";
    cpp << "   ops = \n{\n";

    for (auto &i : instructions)
    {
        for (auto code : i.getOPCodes())
            cpp << "      {0b" + code + ", &" + name + "::" + i.name + "<0b" + code + ">},\n";
    }


    cpp << "};";
    for(auto& m: external_memory)
    {
        cpp << m.getInit();
    }
    cpp << "\n}\n";

    cpp << generateDisplay();

    cpp << "void " + name + "::simulate(std::size_t i)\n{\n"
                            "for (;i-->0;)\n"
                            "{\n"
                            "   auto val = fetch();\n"
                            "   if(!ops.contains(val.val()))\n"
                            "{\n"
                            "std::cerr << \"instruction \" << val.bin() << \" unknown\\n\";\n"
                            "break;\n"
                            "}\n"
                            "   (this->*ops[val.val()])();\n"
                            "}\n";
    cpp << "}\n";


    for(auto m : external_memory)
    {
        cpp << m.getFunction(name);
    }
    // cpp << "void "+name+"::flash(std::vector<uint8_t> rom)\n"
    // "{\n"
    // "for(std::size_t i = 0; i < rom.size(); i++)"
    //     "rom_map[i] = rom[i];\n"
    // "}\n\n";

    // cpp << "bitset "+name+"::rom(bitset val)\n"
    // "{\n"
    // "if(rom_map.contains(val.val())) return bitset({rom_map[val.val()]},8);\n"
    // "return bitset({0},8);\n"
    // "}\n";
    // cpp << "uint8_t* "+name+"::ram(bitset val)\n"
    // "{\n"
    // "if(!ram_map.contains(val.val()))\n"
    // "   ram_map[val.val()] = 0;\n"
    // "return &ram_map[val.val()];\n"
    // "}\n";

    cpp << "bitset "+name+"::fetch()\n"
    "{\n"
    + fetch.getCode(name) +
    "}\n";

    cpp << "void "+name+"::set(AddressInfo info, bitset data)\n{\nset_mem(&memory[0], info, data);\n}\n";
    cpp << "void "+name+"::set(bitset& dest, bitset data)\n{\ndest=data;\n}\n";
    cpp << "void "+name+"::set(std::vector<AddressInfo> info, bitset data)\n{\n"
    "for(std::size_t i = info.size(); i --> 0;)\n"    
    "{\n"
    "set_mem(&memory[0], info[i], data);\n"
    "data = data >> info[i].length;\n"
    "}\n}\n";

    cpp.close();

    std::ofstream cmake("out/CMakeLists.txt", std::ios::trunc);
    cmake << generateCMakeFile();
    cmake.close();

    // std::ofstream main("out/src/main.cpp", std::ios::trunc);
    // main << generateMainFile();
    // main.close();
}