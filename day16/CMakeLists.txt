cmake_minimum_required(VERSION 3.16)

project(day16)

# C++20 standard
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

# Build type
set(CMAKE_BUILD_TYPE Debug) 
#set(CMAKE_BUILD_TYPE Release) # Make it release build to add -O3 and -DNDEBUG flags
add_compile_options(-march=native)

# setting compiler flags
add_compile_options(-Wall -Wextra -Wpedantic)

# Include headers
include_directories("../include")

# Glob files
file(GLOB SOURCES "src/*.cpp")

# Compile binary
add_executable(day16 ${SOURCES})

# add input files
configure_file(test_input.txt test_input.txt)
configure_file(input.txt input.txt)
