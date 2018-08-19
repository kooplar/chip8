#pragma once

#include <string>
#include <unordered_map>
#include <functional>

namespace chip8{

enum class Chip8Opcodes
{
    UNDEFINED,
    _0NNN,
    _00E0, // Clears the screen
    _00EE, // Returns from a subroutine
    _1NNN,
    _2NNN, // Calls subroutine at NNN
    _3XNN,
    _4XNN,
    _5XY0,
    _6XNN,
    _7XNN,
    _8XY0,
    _8XY1,
    _8XY2,
    _8XY3,
    _8XY4, // 0x8XY4 - Adds VY to VX. VF is set to 1 when there is a carry or 0 when there isn't
    _8XY5,
    _8XY6,
    _8XY7,
    _8XYE,
    _9XY0,
    _ANNN, // ANNN: Sets I to the address NNN
    _BNNN,
    _CXNN,
    _DXYN,
    _EX9E,
    _EXA1,
    _FX07,
    _FX0A,
    _FX15,
    _FX18,
    _FX1E,
    _FX29,
    _FX33,
    _FX55,
    _FX65
};

class Chip8 {
    public:
        Chip8(const std::string& game_name);

        Chip8Opcodes decode_opcode(unsigned short opcode);
        const std::string& get_game_name() const;
        void emulate_cycle();

        //define a stream operator << which will dump all the info
        // then we dont need to the dump function anymore

    /* systems memory map: */
    /* 0x000-0x1FF - Chip 8 interpreter (contains font set in emu) */
    /* 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F) */
    /* 0x200-0xFFF - Program ROM and work RAM */
    private:
        static constexpr short memory_size = 4096;
        unsigned char memory[memory_size]{0}; // 4kb of memory
        unsigned short opcode{}; // 35 possible opcodes
        unsigned char vr_registers[16]{};  //15 general regsiters + carry flag
        unsigned short index_register{}; //16 bit register for memory adresses
        unsigned short pc{0x200}; //program counter
        unsigned char gfx[64 *32]{}; // total pixels = 2048
        unsigned char delay_timer{};
        unsigned char sound_timer{};
        unsigned short stack[16]{};
        unsigned short sp{}; //stack pointer
        unsigned char key[16]{}; // hex based keypad 0x0-0xF
        std::string game_name;
        static std::unordered_map<Chip8Opcodes, std::function<void(Chip8&)>> opcode_to_func;

        std::string dump() const;
        void dump_to_stdout() const;
        void init_opcode_to_func_map();
        void do_0NNN();
        void do_00E0();
        void do_00EE();
        void do_2NNN();
        void do_8XY4();
        void do_ANNN();

};

}
