cmake_minimum_required(VERSION 3.10) # Or a more recent version

# Project name
project(LinkedList)

# Set C++ standard (if using C++)
# set(CMAKE_CXX_STANDARD 17) # Or 14, 20, etc.

# Add source files
file(GLOB SOURCES "src/*.c") # Adjust file extensions if needed

# Add include directories (if you have header files)
include_directories(inc ../list/inc)

# Add executable
add_executable(my_executable ${SOURCES})

# Define DEBUG macro if needed
if(DEBUG_MODE) # example of a variable to enable debugging
    add_compile_definitions(DEBUG)
endif()

# Add libraries (if you're linking with external libraries)
# target_link_libraries(my_executable library1 library2)

# Example: Linking the math library (if needed)
target_link_libraries(my_executable -lm)

# Example: Setting compiler flags
# target_compile_options(my_executable PRIVATE -Wall -Wextra -O2)

target_compile_options(my_executable PRIVATE
    -Wall
    -Wextra
    -O2
    -std=c99
    -pedantic-errors
    -D_POSIX_C_SOURCE=200809L
)

# Example: Add a custom build step
# add_custom_target(custom_step
#     COMMAND some_command
#     DEPENDS my_executable
# )

# Example: install target
# install(TARGETS my_executable DESTINATION bin)
# install(DIRECTORY include/ DESTINATION include)