
file(GLOB_RECURSE ressources ../resources/src/*.cpp ../resources/include/*.hpp)
file(GLOB_RECURSE tests *.c*)

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests ${tests} ${ressources})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

target_include_directories(tests PUBLIC ../src/main ../include ../resources/include)


include(Catch)
catch_discover_tests(tests)
