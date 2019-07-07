#pragma once
#include "chip8_input.h"

namespace chip8{

class Chip8InputTerminal : public Chip8Input
{
    public:
        Chip8InputTerminal(Chip8Internals &chip8_internals);
        ~Chip8InputTerminal();
        Chip8InputTerminal(const Chip8Internals &chip8_internals);
        virtual int read_keypress() override;
        virtual void clear_keypress() override;

};

}
