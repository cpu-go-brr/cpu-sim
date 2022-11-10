
file(GLOB_RECURSE tests *.cpp)
file(GLOB_RECURSE data ../resources/src/*.cpp ../resources/include/*.hpp)


Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests ${tests} ${data})

target_include_directories(tests PUBLIC ../src/main)
target_include_directories(tests PUBLIC ../include)
target_include_directories(tests PUBLIC ../resources/include)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(tests)