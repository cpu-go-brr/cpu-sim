cmake_minimum_required(VERSION 3.0) # setting this is required
project(Intel4004)            # this sets the project name
file(GLOB_RECURSE sources src/*.cpp include/*.hpp)
add_executable(intel4004 ${sources})
target_compile_options(intel4004 PUBLIC -std=c++2a -Wall -Wfloat-conversion -O3)
target_include_directories(intel4004 PUBLIC include)
install(TARGETS intel4004 DESTINATION bin)
install(DIRECTORY resources DESTINATION bin)
set(CPACK_PACKAGE_NAME "Intel4004")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_MONOLITHIC_INSTALL 1)
include(CPack)
