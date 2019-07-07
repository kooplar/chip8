#pragma once
#include "chip8.h"

namespace chip8{

class Chip8Input
{
    public:
        Chip8Input(Chip8Internals &chip8_internals);
        /* Chip8Input(const Chip8Internals &chip8_internals); */
        virtual int read_keypress() = 0;
        virtual void clear_keypress() = 0;

    protected:
        Chip8Internals &chip8_internals;
        /* const Chip8Internals &chip8_internals; */

};


}
