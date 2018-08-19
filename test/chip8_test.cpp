#include "chip8_test_config.h"
#include <iostream>
#include "gtest/gtest.h"
#include "chip8.h"

TEST(TestChip8, ConstructoBadGameFile)
{
    ASSERT_THROW(chip8::Chip8 chip8("invalid_game_path"), std::invalid_argument);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "Hello test\n";
    std::cout << "version major: " << Tutorial_VERSION_MAJOR << "\n";
    std::cout << "version minor: " << Tutorial_VERSION_MINOR << "\n";



    return RUN_ALL_TESTS();
}
