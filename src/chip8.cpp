#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "chip8.h"
#include "utils.h"

namespace chip8 {

std::unordered_map<Chip8Opcodes, std::function<void(Chip8&)>> Chip8::opcode_to_func =\
{
    {Chip8Opcodes::_0NNN, &Chip8::do_0NNN},
    {Chip8Opcodes::_00E0, &Chip8::do_00E0}
};

Chip8::Chip8(const std::string& game_name):
    game_name{game_name}
{
    // Initialize fontset
    for(int i = 0; i < 0x50 /*80*/; i++)
    {
        /* memory[i] = chip8_fontset[i]; */
    }

    std::ifstream rom(game_name, std::ios::binary);

    if (! rom.is_open())
    {
        //TODO raise some exception here
        throw std::invalid_argument("Could not open " + game_name);
    }
    rom.seekg(0, std::ios::end);
    size_t rom_size = rom.tellg();
    rom_size -= 1; // remove EOF from size
    rom.seekg(0, std::ios::beg);

    // TODO test if rom will fit in ram, check for larger than some size
    rom.read((char*)&(memory[0x200]), rom_size);
}

const std::string& Chip8::get_game_name() const
{
    return game_name;
}


void Chip8::init_opcode_to_func_map()
{
    /* opcode_to_func[Chip8Opcodes::_ANNN] = [this](){index_register = opcode & 0x0FFF; pc += 2;}; */
    /* opcode_to_func[Chip8Opcodes::_0NNN] = std::bind(&Chip8::do_0NNN, this); */
    /* opcode_to_func[Chip8Opcodes::_0NNN] = std::bind(&Chip8::do_0NNN, this); */
    /* opcode_to_func[Chip8Opcodes::_2NNN] = std::bind(&Chip8::do_2NNN, this); */
    /* opcode_to_func[Chip8Opcodes::_00E0] = std::bind(&Chip8::do_00E0, this); */
    /* opcode_to_func[Chip8Opcodes::_00EE] = std::bind(&Chip8::do_00EE, this); */
    /* opcode_to_func[Chip8Opcodes::_ANNN] = std::bind(&Chip8::do_ANNN, this); */
}

void Chip8::do_0NNN()
{
}
void Chip8::do_00E0()
{
}
void Chip8::do_00EE()
{
}
void Chip8::do_2NNN()
{
    stack[sp] = pc;
    ++sp;
    pc = opcode & 0x0FFF;
}
void Chip8::do_8XY4()
{
    unsigned char X = (opcode & 0x0F00) >> 8;
    unsigned char Y = (opcode & 0x00F0) >> 4;
    vr_registers[0xF] = 0;

    if(vr_registers[X] > ( 0xFF - vr_registers[Y]))
        vr_registers[0xF] = 1; // carry

    vr_registers[X] += vr_registers[Y];
    pc += 2;
}


std::string Chip8::dump() const
{
    std::string output("Memory:\n");
    std::string mem_in_string((char*)&memory, memory_size);
    output.append(string_to_hex(mem_in_string));

    return output;
}

void Chip8::dump_to_stdout() const
{
    std::cout << dump() << "\n";
}

Chip8Opcodes Chip8::decode_opcode(unsigned short opcode)
{
    Chip8Opcodes decoded_opcode{Chip8Opcodes::UNDEFINED};

    switch(opcode & 0xF000)
    {
        case 0x0000:
            switch(opcode & 0x00FF)
            {
                case 0x00E0:
                    decoded_opcode = {Chip8Opcodes::_00E0};
                    break;
                case 0x00EE:
                    decoded_opcode = {Chip8Opcodes::_00EE};
                    break;
                default:
                    decoded_opcode = {Chip8Opcodes::UNDEFINED};
                    break;
            }
            break;

        case 0xA000:
            decoded_opcode = Chip8Opcodes::_ANNN;
            break;
        case 0x2000:
            decoded_opcode = Chip8Opcodes::_2NNN;
            break;

        // 0x8XY#
        case 0x8000:
            switch(opcode & 0x000F)
            {
                case 0x0004:
                    decoded_opcode = Chip8Opcodes::_8XY4;
                    break;
            }
            break;

        default:
            decoded_opcode = {Chip8Opcodes::UNDEFINED};
    }

    if(decoded_opcode == Chip8Opcodes::UNDEFINED)
    {
        dump_to_stdout();
        std::cout << "Unknown opcode hex: " << std::hex << opcode << " \n";
        std::cout << "Unknown opcode: " << opcode << " \n";
        throw std::invalid_argument("bad opcode");
    }
    return decoded_opcode;
}

//TODO create a map of <opcode, function>
// where opcode is some constant given by the decode(opcode)
// and returns something like OPCODE_0000. then just call the function
// at that index and pass in the opcode
// could just declare a whole bunch of (35) opcode functions
// or maybe std::function
// * create google tests for the decode(), then add all possible decodes
// * add google tests for every opcode
// * then look at the gfx stuff
void Chip8::emulate_cycle()
{
    // fetch opcode
    // decode opcode
    // execute opcode
    // update timers
    //

    //merge 2 bytes from memory
    opcode = memory[pc] << 8 | memory[pc + 1];

    Chip8::opcode_to_func[Chip8::decode_opcode(opcode)](*this);

    // Update timers
    if(delay_timer > 0)
        --delay_timer;

    if(sound_timer > 0)
    {
        if(sound_timer == 1)
        {
            std::cout << "BEEP!\n";
        }
        --sound_timer;
    }
}

void Chip8::do_ANNN()
{
    index_register = opcode & 0x0FFF;
    pc += 2;
}


}


