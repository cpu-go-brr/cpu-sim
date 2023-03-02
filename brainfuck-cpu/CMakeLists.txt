cmake_minimum_required(VERSION 3.0) # setting this is required
project(BFCPU)            # this sets the project name
file(GLOB_RECURSE sources src/*.cpp include/*.hpp)
add_executable(bfcpu ${sources})
target_compile_options(bfcpu PUBLIC -std=c++2a -Wall -Wfloat-conversion)
target_include_directories(bfcpu PUBLIC include)
install(TARGETS bfcpu DESTINATION bin)
install(DIRECTORY resources DESTINATION bin)
set(CPACK_PACKAGE_NAME "BFCPU")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_MONOLITHIC_INSTALL 1)
include(CPack)
