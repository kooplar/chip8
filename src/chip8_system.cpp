#include "chip8_system.h"

namespace chip8{

Chip8System::Chip8System(Chip8 *chip8, Chip8Gfx *gfx, Chip8Input *input):
    m_chip8(chip8), m_gfx(gfx), m_input(input)
{
}

void Chip8System::run(){

    for(;;)
    {
        try{

            /* input.read_keypress(); */
            m_chip8->emulate_cycle();
            /* input.clear_keypress(); */
        } catch(std::exception){
            m_chip8->dump_internals();
            exit(1);
        }
        /* chip8.dump_internals(); */
        if(m_chip8->draw)
        {
            m_chip8->dump_internals();
            m_input->clear_keypress();
            m_gfx->draw();
            m_chip8->draw = false;
            m_input->read_keypress();
        }
        /* std::this_thread::sleep_for(std::chrono::milliseconds(020)); */
    }
}

}
