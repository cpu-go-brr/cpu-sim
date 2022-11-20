

MACRO(SUBDIRLIST result curdir)
FILE(GLOB children ${curdir}/*) # This was changed
message(${curdir})

SET(dirlist "")
FOREACH(child ${children})
    IF(IS_DIRECTORY ${child}) # This was changed
        LIST(APPEND dirlist ${child})
    ENDIF()
ENDFOREACH()
SET(${result} ${dirlist})
ENDMACRO()




file(GLOB_RECURSE ressources ../resources/standard/src/*.cpp ../resources/fbitset/src/*.cpp ../resources/abitset/src/*.cpp ../resources/abitset/src/*.cpp)
file(GLOB_RECURSE tests *.c*)


find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests ${tests} ${ressources})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)


target_include_directories(tests PUBLIC ../src/main ../include ../resources/)
SUBDIRLIST(subdirs ../resources)
FOREACH(subdir ${subdirs})
target_include_directories(tests PUBLIC ${subdir}/include)

ENDFOREACH()

include(Catch)
catch_discover_tests(tests)
