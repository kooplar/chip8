cmake_minimum_required (VERSION 2.8.2)
project (chip8)
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/chip8_config.h.in"
  "${PROJECT_BINARY_DIR}/chip8_config.h"
  )
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


# Now simply link against gtest or gtest_main as needed. Eg
add_library (chip8_lib chip8.cpp utils.cpp)
add_executable(chip8 main.cpp)
target_link_libraries(chip8 chip8_lib)
