cmake_minimum_required (VERSION 2.8.2)
project (chip8)
set (CHIP8_VERSION_MAJOR 1)
set (CHIP8_VERSION_MINOR 0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/${CMAKE_BUILD_TYPE})

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/chip8_config.h.in"
  "${PROJECT_BINARY_DIR}/chip8_config.h"
  )
# add the binary tree to the search path for include files
# so that we will find chip8_config.h
include_directories("${PROJECT_BINARY_DIR}")


# Now simply link against gtest or gtest_main as needed. Eg
add_library (chip8_lib src/chip8.cpp src/utils.cpp )
target_include_directories(chip8_lib
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/chip8>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_compile_options(chip8_lib PRIVATE -Werror)
target_compile_features(chip8_lib PRIVATE cxx_std_11)


add_executable(chip8 src/main.cpp)
target_link_libraries(chip8 chip8_lib)

add_subdirectory (test)
