#include "chip8_system.h"

#include <thread>

namespace chip8{

Chip8System::Chip8System(Chip8 *chip8, Chip8Gfx *gfx, Chip8Input *input):
    m_chip8(chip8), m_gfx(gfx), m_input(input)
{
}

void Chip8System::run(){

    for(;;)
    {
        try{

            m_chip8->emulate_cycle();
        } catch(std::exception){
            m_chip8->dump_internals();
            exit(1);
        }
        /* chip8.dump_internals(); */
        if(m_chip8->draw)
        {
            m_chip8->dump_internals();
            m_gfx->draw();
            m_chip8->draw = false;
            /* m_input->read_keypress(); */
            //TODO this still causes some input to be missed
            m_input->clear_keypress();
            //60fps 1000 milli / 60 = 16
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            /* std::this_thread::sleep_for(std::chrono::milliseconds(16)); */
        }
    }
}

}
