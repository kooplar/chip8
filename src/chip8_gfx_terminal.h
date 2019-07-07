#include "chip8_gfx.h"
#include "chip8.h"

namespace chip8{

class Chip8GfxTerminal : public Chip8Gfx
{
    public:
        Chip8GfxTerminal(const Chip8Internals &chip8_internals);
        void draw();

};


}
