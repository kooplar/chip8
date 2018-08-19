#include "chip8_test_config.h"
#include <iostream>
#include "gtest/gtest.h"


int main(int argc, char **argv)
{
    std::cout << "Hello test\n";
    std::cout << "version major: " << Tutorial_VERSION_MAJOR << "\n";
    std::cout << "version minor: " << Tutorial_VERSION_MINOR << "\n";

    return 0;
}
