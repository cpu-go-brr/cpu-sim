cmake_minimum_required(VERSION 3.0) # setting this is required
project(cgen)            # this sets the project name

###############################################################################
## file globbing ##############################################################
###############################################################################

# These instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables 
# `sources` and `data`.
file(GLOB_RECURSE sources src/*.cpp include/*.hpp)
file(GLOB_RECURSE data resources/src/*.cpp resources/include/*.hpp)
#file(GLOB_RECURSE data out/*.cpp out/*.hpp)

# You can use set(sources src/main.cpp) etc if you don't want to
# use globbing to find files automatically.

###############################################################################
## target definitions #########################################################
###############################################################################

# The data is just added to the executable, because in some IDEs (QtCreator) 
# files are invisible when they are not explicitly part of the project.
add_executable(cgen ${sources} ${data})

# Just for example add some compiler flags.
target_compile_options(cgen PUBLIC -std=c++2a -Wall -Wfloat-conversion)


set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

# This allows to include files relative to the root of the src directory with a <> pair
target_include_directories(cgen PUBLIC src/main)
target_include_directories(cgen PUBLIC include)
target_include_directories(cgen PUBLIC resources/include)
#target_include_directories(cgen PUBLIC out)

# This copies all resource files in the build directory.
# We need this, because we want to work with paths relative to the executable.
file(COPY ${data} DESTINATION resources)

###############################################################################
## dependencies ###############################################################
###############################################################################

# This defines the variables Boost_LIBRARIES that containts all library names
# that we need to link into the program.

target_link_libraries(cgen PUBLIC
  pthread
  yaml-cpp
  matheval
)

###############################################################################
## testing ####################################################################
###############################################################################

# This is for our testing framework,
# we don't add REQUIRED because it's just for testing.
# People who might want to build the project to use it should not be required
# to install testing dependencies.

enable_testing()
add_subdirectory(tests)
###############################################################################
## packaging ##################################################################
###############################################################################

# All install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS cgen DESTINATION bin)

# This is basically a repeat of the file copy instruction that copies the
# resources in the build directory, but here we tell cmake that we want it
# in the package.
install(DIRECTORY resources DESTINATION bin)

# Now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here.
set(CPACK_PACKAGE_NAME "cgen")
set(CPACK_PACKAGE_VERSION "1.0.0")

# We don't want to split our program up into several incomplete pieces.
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)