cmake_minimum_required(VERSION 3.0) # setting this is required
project(Intel6502)            # this sets the project name
file(GLOB_RECURSE sources src/*.cpp include/*.hpp)
add_executable(intel6502 ${sources})
target_compile_options(intel6502 PUBLIC -std=c++2a -Wall -Wfloat-conversion)
target_include_directories(intel6502 PUBLIC include)
install(TARGETS intel6502 DESTINATION bin)
install(DIRECTORY resources DESTINATION bin)
set(CPACK_PACKAGE_NAME "Intel6502")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_MONOLITHIC_INSTALL 1)
include(CPack)
