#include "generator.hpp"
#include <fstream>

ADD_GENERATOR(Library);

void LibraryGenerator::generate(CPUDescription::CPU cpu, std::filesystem::path out)
{
    std::filesystem::create_directories(out);

    generateStandard(cpu, out);
    std::filesystem::copy(getExecutablePath()/"resources/abitset", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy(getExecutablePath()/"resources/fbitset", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy(getExecutablePath()/"resources/scripts", out, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);

    std::ofstream settings(out / ("include/settings.hpp"), std::ios::trunc);
    settings << "#pragma once\n"
                "\n"
                "// Define used bitset (ABITSET, FBITSET)\n"
                "#define ABITSET\n"
                "\n"
                "// Mute all prints\n"
                "// #define NO_PRINT\n"
                "// #define NO_CPPSTD\n";
    settings.close();

    std::ofstream pcfile(out / (cpu.getLowerName() + ".pc.in"), std::ios::trunc);

    pcfile << "prefix=@CMAKE_INSTALL_PREFIX@\n"
              "exec_prefix=@CMAKE_INSTALL_PREFIX@\n"
              "libdir=${exec_prefix}/@CMAKE_INSTALL_LIBDIR@\n"
              "includedir=${prefix}/@CMAKE_INSTALL_INCLUDEDIR@\n"
              "\n"
              "Name: " +
                  cpu.getName() + "\n"
                             "Description: " +
                  cpu.getDescription() + "\n"
                                    "Version: 1.0.0\n"
                                    "\n"
                                    "Requires:\n"
                                    "Cflags: -I${includedir} -std=c++2a -Wall -Wfloat-conversion";
    pcfile.close();

    std::ofstream cmake(out / "CMakeLists.txt", std::ios::trunc);

    cmake << "cmake_minimum_required(VERSION 3.5)\n"
             "project("+ cpu.getLowerName() +" VERSION 1.0.0 LANGUAGES CXX)\n"
             "\n"
             "set(DEFAULT_BUILD_TYPE \"Release\")\n"
             "\n"
             "if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)\n"
             "  message(STATUS \"Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.\")\n"
             "  set(CMAKE_BUILD_TYPE \"${DEFAULT_BUILD_TYPE}\" CACHE STRING \"Choose the type of build.\" FORCE)\n"
             "  # Set the possible values of build type for cmake-gui\n"
             "  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS \"Debug\" \"Release\" \"MinSizeRel\" \"RelWithDebInfo\")\n"
             "endif()\n"
             "\n"
             "include(GNUInstallDirs)\n"
             "\n"
             "\n"
             "file(GLOB_RECURSE SOURCE_FILES src/*.cpp)\n"
             "add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})\n"
             "\n"
             "target_include_directories(${PROJECT_NAME} PUBLIC\n"
             "    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>\n"
             "    $<INSTALL_INTERFACE:include>\n"
             "    PRIVATE src)\n"
             "\n"
             "set_target_properties(${PROJECT_NAME} PROPERTIES\n"
             "    VERSION ${PROJECT_VERSION}\n"
             "    SOVERSION 1)\n"
             "\n"
             "install(TARGETS ${PROJECT_NAME} EXPORT MyLibConfig\n"
             "    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}\n"
             "    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}\n"
             "    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})\n"
             "install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})\n"
             "\n"
             "install(EXPORT MyLibConfig DESTINATION share/MyLib/cmake)\n"
             "\n"
             "export(TARGETS ${PROJECT_NAME} FILE MyLibConfig.cmake)\n";

    cmake.close();
}