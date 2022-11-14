  cmake_minimum_required(VERSION 3.0) # setting this is required
project(Intel4004)            # this sets the project name
file(GLOB_RECURSE sources src/*.cpp include/*.hpp)
add_executable(simulator ${sources})
target_compile_options(simulator PUBLIC -std=c++2a -Wall -Wfloat-conversion)
target_include_directories(simulator PUBLIC include)
install(TARGETS simulator DESTINATION bin)
install(DIRECTORY resources DESTINATION bin)
set(CPACK_PACKAGE_NAME "Intel4004")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_MONOLITHIC_INSTALL 1)
include(CPack)
