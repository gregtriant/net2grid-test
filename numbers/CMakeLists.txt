cmake_minimum_required(VERSION 3.10) # Or a more recent version

# Project name
project(LinkedList)

# Add source files
file(GLOB SOURCES "src/*.c")

# Add include directories (if you have header files)
include_directories(inc ../list/inc)

# Add executable
add_executable(my_executable ${SOURCES})

# Define DEBUG macro if needed
if(DEBUG_MODE)
    add_compile_definitions(DEBUG)
endif()

target_link_libraries(my_executable -lm)

target_compile_options(my_executable PRIVATE
    -Wall
    -Wextra
    -O2
    -std=c99
    -pedantic-errors
    -D_POSIX_C_SOURCE=200809L
)
