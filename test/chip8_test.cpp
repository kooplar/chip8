#include "chip8_test_config.h"
#include "chip8.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(TestChip8, Chip8_constructor)
{
    ASSERT_THROW(chip8::Chip8 chip8("invalid_game_path"), std::invalid_argument);
}

TEST(TestChip8, Chip8_decode_opcode)
{
    //TODO fixhard coding of this path
    chip8::Chip8 chip8("../test/data/test_rom_1");
    unsigned short opcode{};

    opcode = 0x0123;
    EXPECT_EQ(chip8::Chip8Opcodes::_0NNN, chip8.decode_opcode(opcode));

    opcode = 0x00E0;
    EXPECT_EQ(chip8::Chip8Opcodes::_00E0, chip8.decode_opcode(opcode));

    opcode = 0x00EE;
    EXPECT_EQ(chip8::Chip8Opcodes::_00EE, chip8.decode_opcode(opcode));

    opcode = 0x1234;
    EXPECT_EQ(chip8::Chip8Opcodes::_1NNN, chip8.decode_opcode(opcode));

    opcode = 0x2234;
    EXPECT_EQ(chip8::Chip8Opcodes::_2NNN, chip8.decode_opcode(opcode));

    opcode = 0x3234;
    EXPECT_EQ(chip8::Chip8Opcodes::_3XNN, chip8.decode_opcode(opcode));

    opcode = 0x4234;
    EXPECT_EQ(chip8::Chip8Opcodes::_4XNN, chip8.decode_opcode(opcode));

    opcode = 0x5230;
    EXPECT_EQ(chip8::Chip8Opcodes::_5XY0, chip8.decode_opcode(opcode));

    opcode = 0x6230;
    EXPECT_EQ(chip8::Chip8Opcodes::_6XNN, chip8.decode_opcode(opcode));

    opcode = 0x7230;
    EXPECT_EQ(chip8::Chip8Opcodes::_7XNN, chip8.decode_opcode(opcode));

    opcode = 0x8120;
    EXPECT_EQ(chip8::Chip8Opcodes::_8XY0, chip8.decode_opcode(opcode));
    opcode = 0x8121;
    EXPECT_EQ(chip8::Chip8Opcodes::_8XY1, chip8.decode_opcode(opcode));
    opcode = 0x8122;
    EXPECT_EQ(chip8::Chip8Opcodes::_8XY2, chip8.decode_opcode(opcode));
    opcode = 0x8123;
    EXPECT_EQ(chip8::Chip8Opcodes::_8XY3, chip8.decode_opcode(opcode));
    opcode = 0x8124;
    EXPECT_EQ(chip8::Chip8Opcodes::_8XY4, chip8.decode_opcode(opcode));
    opcode = 0x8125;
    EXPECT_EQ(chip8::Chip8Opcodes::_8XY5, chip8.decode_opcode(opcode));
    opcode = 0x8126;
    EXPECT_EQ(chip8::Chip8Opcodes::_8XY6, chip8.decode_opcode(opcode));
    opcode = 0x8127;
    EXPECT_EQ(chip8::Chip8Opcodes::_8XY7, chip8.decode_opcode(opcode));
    opcode = 0x812E;
    EXPECT_EQ(chip8::Chip8Opcodes::_8XYE, chip8.decode_opcode(opcode));

    opcode = 0x9120;
    EXPECT_EQ(chip8::Chip8Opcodes::_9XY0, chip8.decode_opcode(opcode));

    opcode = 0xA123;
    EXPECT_EQ(chip8::Chip8Opcodes::_ANNN, chip8.decode_opcode(opcode));

    opcode = 0xB123;
    EXPECT_EQ(chip8::Chip8Opcodes::_BNNN, chip8.decode_opcode(opcode));

    opcode = 0xC123;
    EXPECT_EQ(chip8::Chip8Opcodes::_CXNN, chip8.decode_opcode(opcode));

    opcode = 0xD123;
    EXPECT_EQ(chip8::Chip8Opcodes::_DXYN, chip8.decode_opcode(opcode));

    opcode = 0xE12E;
    EXPECT_EQ(chip8::Chip8Opcodes::_EX9E, chip8.decode_opcode(opcode));
    opcode = 0xE121;
    EXPECT_EQ(chip8::Chip8Opcodes::_EXA1, chip8.decode_opcode(opcode));

    opcode = 0xF107;
    EXPECT_EQ(chip8::Chip8Opcodes::_FX07, chip8.decode_opcode(opcode));
    opcode = 0xF10A;
    EXPECT_EQ(chip8::Chip8Opcodes::_FX0A, chip8.decode_opcode(opcode));
    opcode = 0xF115;
    EXPECT_EQ(chip8::Chip8Opcodes::_FX15, chip8.decode_opcode(opcode));
    opcode = 0xF118;
    EXPECT_EQ(chip8::Chip8Opcodes::_FX18, chip8.decode_opcode(opcode));
    opcode = 0xF11E;
    EXPECT_EQ(chip8::Chip8Opcodes::_FX1E, chip8.decode_opcode(opcode));
    opcode = 0xF129;
    EXPECT_EQ(chip8::Chip8Opcodes::_FX29, chip8.decode_opcode(opcode));
    opcode = 0xF133;
    EXPECT_EQ(chip8::Chip8Opcodes::_FX33, chip8.decode_opcode(opcode));
    opcode = 0xF155;
    EXPECT_EQ(chip8::Chip8Opcodes::_FX55, chip8.decode_opcode(opcode));
    opcode = 0xF165;
    EXPECT_EQ(chip8::Chip8Opcodes::_FX65, chip8.decode_opcode(opcode));

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "test version major: " << Tutorial_VERSION_MAJOR << "\n";
    std::cout << "test version minor: " << Tutorial_VERSION_MINOR << "\n";

    return RUN_ALL_TESTS();
}
