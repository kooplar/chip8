#include <iostream>
#include "chip8.h"

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
    //set up graphics
    //set up input

    Chip8 chip8(argv[1]);

    //emulaion loop
    for(;;)
    {
        chip8.emulate_cycle();
        //chip 8 emulate one cycle
        //if draw==true, draw screen. the system does not draw every cycle
        //read key press
        break;
    }

}
