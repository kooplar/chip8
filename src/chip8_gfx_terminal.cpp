#include "chip8_gfx_terminal.h"
#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>
#include <sstream>

namespace chip8{

Chip8GfxTerminal::Chip8GfxTerminal(const Chip8Internals &chip8_internals) : Chip8Gfx(chip8_internals)
{
}
void Chip8GfxTerminal::draw()
{
    std::stringstream output;
    output << "\nChip8GfxTerminal::draw";
    for(int i =0 ; i <chip8_internals.gfx.size(); i++)
    {
        if( (i % 64) == 0)
            output << "\n" << std::setfill('0') << std::setw(4) << i << " ";
        if (chip8_internals.gfx[i])
            output << "█";
        else
            output << ".";
    }
    output << "\n";
    std::cout << output.str();

}


}
