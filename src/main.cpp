#include <iostream>
#include <chrono>
#include <thread>

#include "chip8.h"

#include "chip8_gfx_terminal.h"
#include "chip8_input_terminal.h"

#include "chip8_system.h"


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
    Chip8InputTerminal input(chip8.internals);

    //TODO shared ptr
    Chip8System chip8_system(&chip8, &gfx, &input);
    /* Chip8GfxTerminal gfx(chip8.get_internals()); */
    //set up input
    //set up sound

    //emulation loop
    for (;;)
    {
        chip8_system.run();
    }
    /* for(;;) */
    /* { */
    /*     try{ */

    /*         /1* input.read_keypress(); *1/ */
    /*         chip8.emulate_cycle(); */
    /*         /1* input.clear_keypress(); *1/ */
    /*     } catch(std::exception){ */
    /*         chip8.dump_internals(); */
    /*         exit(1); */
    /*     } */
    /*     /1* chip8.dump_internals(); *1/ */
    /*     if(chip8.draw) */
    /*     { */
    /*         chip8.dump_internals(); */
    /*         input.clear_keypress(); */
    /*         gfx.draw(); */
    /*         chip8.draw = false; */
    /*         input.read_keypress(); */
    /*     } */
    /*     /1* std::this_thread::sleep_for(std::chrono::milliseconds(020)); *1/ */
    /* } */

}
