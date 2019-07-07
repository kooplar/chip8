#pragma once
#include "chip8.h"
#include "chip8_gfx.h"
#include "chip8_input.h"

namespace chip8{

class Chip8System{
    public:
        //TODO shard ptr
        Chip8System(Chip8 *chip8, Chip8Gfx *fx, Chip8Input *input);
        void run();
    private:
        Chip8 *m_chip8;
        Chip8Gfx *m_gfx;
        Chip8Input *m_input;
};
}
