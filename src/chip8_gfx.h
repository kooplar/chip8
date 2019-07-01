#pragma once
#include "chip8.h"

namespace chip8{

class Chip8Gfx
{
    public:
        Chip8Gfx(const Chip8Internals &chip8_internals);
        virtual void draw() = 0;

    protected:
        const Chip8Internals &chip8_internals;

};


}
