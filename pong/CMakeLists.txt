cmake_minimum_required(VERSION 3.0) # setting this is required
project(Pong)            # this sets the project name
file(GLOB_RECURSE sources src/*.cpp include/*.hpp)
add_executable(pong ${sources})
target_compile_options(pong PUBLIC -std=c++2a -Wall -Wfloat-conversion)
target_include_directories(pong PUBLIC include)
install(TARGETS pong DESTINATION bin)
install(DIRECTORY resources DESTINATION bin)
set(CPACK_PACKAGE_NAME "Pong")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_MONOLITHIC_INSTALL 1)
include(CPack)
