#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <stdint.h>
#include <memory>

namespace chip8{

enum class Chip8Opcodes
{
    UNDEFINED,
    _0NNN,
    _00E0, // Clears the screen
    _00EE, // Returns from a subroutine
    _1NNN, // Jump to location NNN
    _2NNN, // Calls subroutine at NNN
    _3XNN, // Skip next instruction if Vx = NN
    _4XNN, // Skip next instruction if Vx != NN
    _5XY0, // Skips next instruction if Vx = Vy
    _6XNN, // Set Vx = NN
    _7XNN, // Set Vx += NN
    _8XY0, // Set Vx = Vy
    _8XY1, // Set Vx |= Vy
    _8XY2, // Set Vx &= Vy
    _8XY3, // Set Vx ^= Vy
    _8XY4, // Set Vx += Vy. VF is set to 1 when there is a carry or 0 when there isn't
    _8XY5, // Set Vx -= Vy. VF is set to 1 if Vx > Vy (before the -=, otherwise 0)
    _8XY6, // Set Vx = Vx SHR 1. If the least-significat bit of Vx is 1, then VF is 1 else 0. Then, Vx /= 2
    _8XY7, // Set Vx -= Vy - Vx. VF is set to 1 if Vy > V0 (before the -=, otherwise 0)
    _8XYE, // Set Vx = Vx SHL 1. If the least-significat bit of Vx is 1, then VF is 1 else 0. Then, Vx *= 2
    _9XY0, // Skip next instruction if Vx != Vy
    _ANNN, // ANNN: Sets I to the address NNN
    _BNNN, // Jump to location NN + V0
    _CXNN, // Set Vx = random byte & NN
    _DXYN, // Display n-byte sprite starting at memory location I at (Vx,Vy), set Vf = collision.
    _EX9E, // Skip next instruction (pc += 2 ) if key in position Vx is pressed
    _EXA1, // Skip next instruction (pc += 2 ) if key in position Vx is NOT  pressed
    _FX07, // Set Vx = delay timer value
    _FX0A, // Wait for a key press and store it in Vx
    _FX15, // Set delay timer = Vx
    _FX18, // Set sound timer = Vx
    _FX1E, // I += Vx
    _FX29, // Set I = location of sprite for digit Vx
    _FX33, // Store BCD representation of Vx in memory locations I, I+1, I+2
    _FX55, // Store registers V0 through Vx in memory starting at location I
    _FX65, // Store memory locations from I to X into V0 to Vx
};

struct Chip8Internals
{
    /* systems memory map: */
    /* 0x000-0x1FF - Chip 8 interpreter (contains font set in emu) */
    /* 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F) */
    /* 0x200-0xFFF - Program ROM and work RAM */
    std::array<uint8_t, 4096> memory;
    std::array<uint16_t, 16> stack;
    std::array<uint8_t, 16> V;  //15 general regsiters + carry flag
    std::array<uint8_t, 64 * 32> gfx; // screen size is 64 x 32
    uint8_t key[16]; // hex based keypad 0x0-0xF; 1 = pressed 0 = not pressed
    uint16_t I; //16 bit register for memory adresses
    uint16_t pc; //program counter
    uint16_t sp; //stack pointer
    uint8_t delay_timer;
    uint8_t sound_timer;
};

class Chip8
{
    public:
        Chip8(const std::string& game_name);
        // The idea here is that you can pass in your own initialized internals
        // for testing. if internals are passed in do not initialize them
        Chip8(std::shared_ptr<Chip8Internals> internals, const std::string& game_name);
        static Chip8Opcodes decode_opcode(uint16_t opcode);
        const std::string& get_game_name() const;
        const Chip8Internals& get_internals() const;
        bool draw = false;
        void reset();
        void do_opcode(uint16_t opcode);
        void emulate_cycle();
        void dump_internals();
        // TODO internals should NOT be public, but moving for now to ease development
        Chip8Internals internals;

        //define a stream operator << which will dump all the info
        // then we dont need to the dump function anymore

    private:
        std::string game_name;
        /* Chip8Internals internals; */
        static std::unordered_map<Chip8Opcodes, std::function<void(Chip8&, uint16_t)>> opcode_to_func;

        std::string dump() const;
        void dump_to_stdout() const;
        void init_opcode_to_func_map();
        void do_0NNN(uint16_t);
        void do_00E0(uint16_t);
        void do_00EE(uint16_t);
        void do_1NNN(uint16_t);
        void do_2NNN(uint16_t);
        void do_3XNN(uint16_t);
        void do_4XNN(uint16_t);
        void do_5XY0(uint16_t);
        void do_6XNN(uint16_t);
        void do_7XNN(uint16_t);
        void do_8XY0(uint16_t);
        void do_8XY1(uint16_t);
        void do_8XY2(uint16_t);
        void do_8XY3(uint16_t);
        void do_8XY4(uint16_t);
        void do_8XY5(uint16_t);
        void do_8XY6(uint16_t);
        void do_8XY7(uint16_t);
        void do_8XYE(uint16_t);
        void do_9XY0(uint16_t);
        void do_ANNN(uint16_t);
        void do_BNNN(uint16_t);
        void do_CXNN(uint16_t);
        void do_DXYN(uint16_t);
        void do_EX9E(uint16_t);
        void do_EXA1(uint16_t);
        void do_FX07(uint16_t);
        void do_FX0A(uint16_t);
        void do_FX15(uint16_t);
        void do_FX18(uint16_t);
        void do_FX1E(uint16_t);
        void do_FX29(uint16_t);
        void do_FX33(uint16_t);
        void do_FX55(uint16_t);
        void do_FX65(uint16_t);
};

}
