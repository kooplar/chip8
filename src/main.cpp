#include <iostream>
#include <chrono>
#include <thread>

#include "chip8.h"

#include "chip8_gfx_terminal.h"


//TODO: a class called Chip8System which takes
//the chip8 emu class, the screen (gfx), the sound, then does
//the whole emulation look when you call .start on it (or option to do one
//cycle at a time

using namespace chip8;

void usage(const char* const program_name)
{
    std::cout << "  Usage: " << program_name << " game" << std::endl;
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        std::cout << "No game provided\n";
        usage(argv[0]);
        exit(2);
    }

    Chip8 chip8(argv[1]);
    //set up graphics
    Chip8GfxTerminal gfx(chip8.get_internals());
    //set up input
    //set up sound

    //emulation loop
    for(;;)
    {
        chip8.emulate_cycle();
        if(chip8.draw)
        {
            chip8.dump_internals();
            gfx.draw();
            chip8.draw = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(050));
        /* usleep(100000); */
        //chip 8 emulate one cycle
        //if draw==true, draw screen. the system does not draw every cycle
        //read key press
        /* break; */
    }

}
