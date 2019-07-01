#include <iomanip>
#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <stdlib.h> // rand - TODO switch for c++ api
#include "chip8.h"
#include "utils.h"
// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#Ex9E

#include <chrono>
#include <thread>

namespace chip8 {

std::unordered_map<Chip8Opcodes,
                   std::function<void(Chip8&, uint16_t)>> Chip8::opcode_to_func =\
{
    {Chip8Opcodes::_0NNN, &Chip8::do_0NNN},
    {Chip8Opcodes::_00E0, &Chip8::do_00E0},
    {Chip8Opcodes::_00EE, &Chip8::do_00EE},
    {Chip8Opcodes::_1NNN, &Chip8::do_1NNN},
    {Chip8Opcodes::_2NNN, &Chip8::do_2NNN},
    {Chip8Opcodes::_3XNN, &Chip8::do_3XNN},
    {Chip8Opcodes::_4XNN, &Chip8::do_4XNN},
    {Chip8Opcodes::_5XY0, &Chip8::do_5XY0},
    {Chip8Opcodes::_6XNN, &Chip8::do_6XNN},
    {Chip8Opcodes::_7XNN, &Chip8::do_7XNN},
    {Chip8Opcodes::_8XY0, &Chip8::do_8XY0},
    {Chip8Opcodes::_8XY1, &Chip8::do_8XY1},
    {Chip8Opcodes::_8XY2, &Chip8::do_8XY2},
    {Chip8Opcodes::_8XY3, &Chip8::do_8XY3},
    {Chip8Opcodes::_8XY4, &Chip8::do_8XY4},
    {Chip8Opcodes::_8XY5, &Chip8::do_8XY5},
    {Chip8Opcodes::_8XY6, &Chip8::do_8XY6},
    {Chip8Opcodes::_8XY7, &Chip8::do_8XY7},
    {Chip8Opcodes::_8XYE, &Chip8::do_8XYE},
    {Chip8Opcodes::_9XY0, &Chip8::do_9XY0},
    {Chip8Opcodes::_ANNN, &Chip8::do_ANNN},
    {Chip8Opcodes::_BNNN, &Chip8::do_BNNN},
    {Chip8Opcodes::_CXNN, &Chip8::do_CXNN},
    {Chip8Opcodes::_DXYN, &Chip8::do_DXYN},
    {Chip8Opcodes::_EX9E, &Chip8::do_EX9E},
    {Chip8Opcodes::_EXA1, &Chip8::do_EXA1},
    {Chip8Opcodes::_FX07, &Chip8::do_FX07},
    {Chip8Opcodes::_FX0A, &Chip8::do_FX0A},
    {Chip8Opcodes::_FX15, &Chip8::do_FX15},
    {Chip8Opcodes::_FX18, &Chip8::do_FX18},
    {Chip8Opcodes::_FX1E, &Chip8::do_FX1E},
    {Chip8Opcodes::_FX29, &Chip8::do_FX29},
    {Chip8Opcodes::_FX33, &Chip8::do_FX33},
    {Chip8Opcodes::_FX55, &Chip8::do_FX55},
    {Chip8Opcodes::_FX55, &Chip8::do_FX55},
    {Chip8Opcodes::_FX65, &Chip8::do_FX55},
};

Chip8::Chip8(const std::string& game_name):
    game_name{game_name},
    internals{}
{
    internals.pc = 0x200;

    std::array<uint8_t, 80> fontset =
        { 
          0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
          0x20, 0x60, 0x20, 0x20, 0x70, // 1
          0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
          0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
          0x90, 0x90, 0xF0, 0x10, 0x10, // 4
          0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
          0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
          0xF0, 0x10, 0x20, 0x40, 0x40, // 7
          0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
          0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
          0xF0, 0x90, 0xF0, 0x90, 0x90, // A
          0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
          0xF0, 0x80, 0x80, 0x80, 0xF0, // C
          0xE0, 0x90, 0x90, 0x90, 0xE0, // D
          0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
          0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

    std::copy(std::begin(fontset), std::end(fontset), std::begin(internals.memory) + 0x50);
    for(int y=0; y<16; y++)
    {
        break;
        for(int x=0;x<5; x++)
        {

            uint8_t byte = internals.memory[(y * 5) + x  + 0x50];
            if(byte & 0x80)
                printf("*");
            else
                printf(" ");
            if(byte & 0x40)
                printf("*");
            else
                printf(" ");
            if(byte & 0x20)
                printf("*");
            else
                printf(" ");
            if(byte & 0x10)
                printf("*");
            else
                printf(" ");
            if(byte & 0x08)
                printf("*");
            else
                printf(" ");
            if(byte & 0x04)
                printf("*");
            else
                printf(" ");
            if(byte & 0x02)
                printf("*");
            else
                printf(" ");
            if(byte & 0x01)
                printf("*");
            else
                printf(" ");
        printf("\n");
        }
        printf("\n\n\n");
    }



    std::ifstream rom(game_name, std::ios::binary);

    if (! rom.is_open())
    {
        throw std::invalid_argument("Could not open " + game_name);
    }
    rom.seekg(0, std::ios::end);
    size_t rom_size = rom.tellg();
    rom_size -= 1; // remove EOF from size
    rom.seekg(0, std::ios::beg);

    // TODO test if rom will fit in ram, check for larger than some size
    rom.read((char*)&(internals.memory[0x200]), rom_size);
}

void Chip8::reset()
{
    throw "have not finished implemetnting this";
    internals = {};
    internals.pc = 0x200;
    game_name = "";
}

const Chip8Internals& Chip8::get_internals() const
{
    return internals;
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



// TODO take a stream reference, then can just pass in a
// stdout or stringstream ifwe want to get the string out
std::string Chip8::dump() const
{
    std::string output("Memory:\n");
    std::string mem_in_string((char*)&internals.memory, internals.memory.size());
    output.append(string_to_hex(mem_in_string));

    return output;
}

void Chip8::dump_to_stdout() const
{
    std::cout << dump() << "\n";
}

Chip8Opcodes Chip8::decode_opcode(uint16_t opcode)
{
    Chip8Opcodes decoded_opcode{Chip8Opcodes::UNDEFINED};

    switch(opcode & 0xF000)
    {
        case 0x0000:
            switch(opcode & 0x0FFF)
            {
                case 0x00E0:
                    decoded_opcode = Chip8Opcodes::_00E0;
                    break;
                case 0x00EE:
                    decoded_opcode = Chip8Opcodes::_00EE;
                    break;
                default:
                    decoded_opcode = Chip8Opcodes::_0NNN;
                    break;
            }
            break;
        case 0x1000:
            decoded_opcode = Chip8Opcodes::_1NNN;
            break;
        case 0x2000:
            decoded_opcode = Chip8Opcodes::_2NNN;
            break;
        case 0x3000:
            decoded_opcode = Chip8Opcodes::_3XNN;
            break;
        case 0x4000:
            decoded_opcode = Chip8Opcodes::_4XNN;
            break;
        case 0x5000:
            decoded_opcode = Chip8Opcodes::_5XY0;
            break;
        case 0x6000:
            decoded_opcode = Chip8Opcodes::_6XNN;
            break;
        case 0x7000:
            decoded_opcode = Chip8Opcodes::_7XNN;
            break;
        case 0x8000:
            switch(opcode & 0x000F)
            {
                case 0x0000:
                    decoded_opcode = Chip8Opcodes::_8XY0;
                    break;
                case 0x0001:
                    decoded_opcode = Chip8Opcodes::_8XY1;
                    break;
                case 0x0002:
                    decoded_opcode = Chip8Opcodes::_8XY2;
                    break;
                case 0x0003:
                    decoded_opcode = Chip8Opcodes::_8XY3;
                    break;
                case 0x0004:
                    decoded_opcode = Chip8Opcodes::_8XY4;
                    break;
                case 0x0005:
                    decoded_opcode = Chip8Opcodes::_8XY5;
                    break;
                case 0x0006:
                    decoded_opcode = Chip8Opcodes::_8XY6;
                    break;
                case 0x0007:
                    decoded_opcode = Chip8Opcodes::_8XY7;
                    break;
                case 0x000E:
                    decoded_opcode = Chip8Opcodes::_8XYE;
                    break;
            }
            break;
        case 0x9000:
            return Chip8Opcodes::_9XY0;
        case 0xA000:
            decoded_opcode = Chip8Opcodes::_ANNN;
            break;
        case 0xB000:
            decoded_opcode = Chip8Opcodes::_BNNN;
            break;
        case 0xC000:
            decoded_opcode = Chip8Opcodes::_CXNN;
            break;
        case 0xD000:
            decoded_opcode = Chip8Opcodes::_DXYN;
            break;
        case 0xE000:
            switch(opcode & 0x000F)
            {
                case 0x000E:
                    decoded_opcode = Chip8Opcodes::_EX9E;
                    break;
                case 0x0001:
                    decoded_opcode = Chip8Opcodes::_EXA1;
                    break;
            }
            break;
        case 0xF000:
            switch(opcode & 0x00FF)
            {
                case 0x0007:
                    decoded_opcode = Chip8Opcodes::_FX07;
                    break;
                case 0x000A:
                    decoded_opcode = Chip8Opcodes::_FX0A;
                    break;
                case 0x0015:
                    decoded_opcode = Chip8Opcodes::_FX15;
                    break;
                case 0x0018:
                    decoded_opcode = Chip8Opcodes::_FX18;
                    break;
                case 0x001E:
                    decoded_opcode = Chip8Opcodes::_FX1E;
                    break;
                case 0x0029:
                    decoded_opcode = Chip8Opcodes::_FX29;
                    break;
                case 0x0033:
                    decoded_opcode = Chip8Opcodes::_FX33;
                    break;
                case 0x0055:
                    decoded_opcode = Chip8Opcodes::_FX55;
                    break;
                case 0x0065:
                    decoded_opcode = Chip8Opcodes::_FX65;
                    break;
            }
            break;
        default:
            decoded_opcode = {Chip8Opcodes::UNDEFINED};
    }

    if(decoded_opcode == Chip8Opcodes::UNDEFINED)
    {
        std::cerr << "Unknown opcode hex: " << std::hex << opcode << " \n";
        std::cerr << "Unknown opcode: " << opcode << " \n";
        throw std::invalid_argument("bad opcode");
    }
    return decoded_opcode;
}

void Chip8::emulate_cycle()
{
    // fetch opcode
    // decode opcode
    // execute opcode
    // update timers

    //merge 2 bytes from memory
    uint16_t opcode = internals.memory[internals.pc] << 8 | internals.memory[internals.pc + 1];
    internals.pc += 2;
    /* std::cout << "pc is now at " << std::hex << internals.pc << " got opcode " << std::hex << opcode << " \n"; */

    do_opcode(opcode);


    // Update timers
    if(internals.delay_timer > 0)
        --internals.delay_timer;

    if(internals.sound_timer > 0)
    {
        if(internals.sound_timer == 1)
        {
            std::cout << "BEEP!\n";
        }
        --internals.sound_timer;
    }
}

void Chip8::do_opcode(uint16_t opcode)
{
    Chip8::opcode_to_func[Chip8::decode_opcode(opcode)](*this, opcode);
}

void Chip8::do_0NNN(uint16_t opcode)
{
    std::cerr << "Detected use of opcode 0NNN";
    throw "opcdoe 0NNN should not be used";
}
void Chip8::do_00E0(uint16_t opcode)
{
    internals.gfx.fill(0);
    draw = true;
}
void Chip8::do_00EE(uint16_t opcode)
{
    internals.pc = internals.stack[internals.sp--];
}
void Chip8::do_1NNN(uint16_t opcode)
{
    internals.pc = opcode & 0x0FFF;
}
void Chip8::do_2NNN(uint16_t opcode)
{
    internals.stack[++internals.sp] = internals.pc;
    internals.pc = opcode & 0x0FFF;
}
void Chip8::do_3XNN(uint16_t opcode)
{
    if(internals.V[(opcode & 0X0F00) >> 8] == (opcode & 0x00FF))
        internals.pc += 2;
}
void Chip8::do_4XNN(uint16_t opcode)
{
    if(internals.V[(opcode & 0X0F00) >> 8] != (opcode & 0x00FF))
        internals.pc += 2;
}
void Chip8::do_5XY0(uint16_t opcode)
{
    if(internals.V[(opcode & 0x0F00) >> 8] == internals.V[(opcode & 0x00F0)>>4])
        internals.pc += 2;
}
void Chip8::do_6XNN(uint16_t opcode)
{
    internals.V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
}
void Chip8::do_7XNN(uint16_t opcode)
{
    internals.V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
}
void Chip8::do_8XY0(uint16_t opcode)
{
    internals.V[(opcode & 0x0F00) >> 8] = internals.V[(opcode & 0x00F0) >> 4];
}
void Chip8::do_8XY1(uint16_t opcode)
{
    internals.V[(opcode & 0x0F00) >> 8] |= internals.V[(opcode & 0x00F0) >> 4];
}
void Chip8::do_8XY2(uint16_t opcode)
{
    internals.V[(opcode & 0x0F00) >> 8] &= internals.V[(opcode & 0x00F0) >> 4];
}
void Chip8::do_8XY3(uint16_t opcode)
{
    internals.V[(opcode & 0x0F00) >> 8] ^= internals.V[(opcode & 0x00F0) >> 4];
}
void Chip8::do_8XY4(uint16_t opcode)
{
    uint8_t X = (opcode & 0x0F00) >> 8;
    uint8_t Y = (opcode & 0x00F0) >> 4;
    internals.V[0xF] = 0;

    if(internals.V[X] > (0xFF - internals.V[Y]))
        internals.V[0xF] = 1;

    internals.V[X] += internals.V[Y];
}
void Chip8::do_8XY5(uint16_t opcode)
{
    uint8_t X = (opcode & 0x0F00) >> 8;
    uint8_t Y = (opcode & 0x00F0) >> 4;
    internals.V[0xF] = 0;

    if(internals.V[X] > internals.V[Y])
        internals.V[0xF] = 1;

    internals.V[X] -= internals.V[Y];
}
void Chip8::do_8XY6(uint16_t opcode)
{
    uint8_t X = (opcode & 0x0F00) >> 8;
    internals.V[0xF] = internals.V[X] & 0x1;
    internals.V[X] >>= 1;
}
void Chip8::do_8XY7(uint16_t opcode)
{
    uint8_t X = (opcode & 0x0F00) >> 8;
    uint8_t Y = (opcode & 0x00F0) >> 4;
    internals.V[0xF] = 0;

    if(internals.V[Y] > internals.V[X])
        internals.V[0xF] = 1;

    internals.V[X] = internals.V[Y] - internals.V[X];
}
void Chip8::do_8XYE(uint16_t opcode)
{
    uint8_t X = (opcode & 0x0F00) >> 8;
    internals.V[0xF] = internals.V[X] & 0x80;
    internals.V[X] <<= 1;
}
void Chip8::do_9XY0(uint16_t opcode)
{
    if(internals.V[(opcode & 0x0F00) >> 8] != internals.V[(opcode & 0x00F0) >> 4])
        internals.pc += 2;
}
void Chip8::do_ANNN(uint16_t opcode)
{
    internals.I = opcode & 0x0FFF;
}
void Chip8::do_BNNN(uint16_t opcode)
{
    internals.pc = (opcode & 0x0FFF) + internals.V[0];
}
void Chip8::do_CXNN(uint16_t opcode)
{
    internals.V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
}
void Chip8::do_DXYN(uint16_t opcode)
{
    uint16_t X = internals.V[(opcode & 0x0F00) >> 8];
    uint16_t Y = internals.V[(opcode & 0x00F0) >> 4];
    uint16_t height = opcode & 0x000F;
    uint16_t pixel = 0;
    internals.V[0xF] = 0;
    draw=true;
    std::cout << std::dec << "adding sprite to (X,Y,h) (" << static_cast<int>(X) << "," << static_cast<int>(Y) << "," << static_cast<int>(height) << ")" << "  opcode hex " << std::hex << opcode << "\n";

    for (int yline = 0; yline < height; yline++)
    {
        pixel = internals.memory[internals.I + yline];
        std::cout << std::hex << "adding " << pixel << "\n";
        for(int xline = 0; xline < 8; xline++)
        {
            if((pixel & (0x80 >> xline)) != 0)
            {
                if(internals.gfx[(X + xline + ((Y + yline) * 64)) % 2048 ] == 1)
                {
                  internals.V[0xF] = 1;
                }
                std::cout << std::dec << " adding " << xline <<  "X,Y " << X+xline << "," << Y+yline  << "\n";
                internals.gfx[X + xline + ((Y + yline) * 64) % 2048] ^= 1;
            }
        }
    }
}
/* void Chip8::do_DXYN(uint16_t opcode) */
/* { */
/*     uint8_t X = internals.V[(opcode & 0x0F00) >> 8]; */
/*     uint8_t Y = internals.V[(opcode & 0x00F0) >> 4]; */
/*     uint8_t height = opcode & 0x000F; */
/*     uint8_t add_byte = 0; */
/*     uint8_t new_byte = 0; */
/*     uint8_t *cur_byte = nullptr; */
/*     internals.V[0xF] = 0; */
/*     std::cout << std::dec << "adding sprite to (X,Y,h) (" << static_cast<int>(X) << "," << static_cast<int>(Y) << "," << static_cast<int>(height) << ")" << "  opcode hex " << std::hex << opcode << "\n"; */

/*     for(int y = 0; y < height; ++y) */
/*     { */
/*         add_byte = internals.memory[internals.I + y]; */
/*         std::cout << "[ " << std::hex << static_cast<int>(add_byte) << std::dec << " ] at position X,Y " << static_cast<int>(X) << "," << static_cast<int>(Y+y)<<"\n"; */
/*         cur_byte = &internals.gfx[static_cast<int>(X) + (64 * (static_cast<int>(Y) + y)) % internals.gfx.size()]; */
/*         new_byte = add_byte ^ *cur_byte; */

/*         if(new_byte & *cur_byte) */
/*             internals.V[0xF] = 1; */

/*         *cur_byte = new_byte; */
/*     } */
/*     draw = true; */
/* } */

void Chip8::do_EX9E(uint16_t opcode)
{
    if(internals.key & (internals.V[(opcode & 0x0F00) >> 8]))
        internals.pc += 2;
}
void Chip8::do_EXA1(uint16_t opcode)
{
    if(internals.key ^ (internals.V[(opcode & 0x0F00) >> 8]))
        internals.pc += 2;
}
void Chip8::do_FX07(uint16_t opcode)
{
    internals.V[(opcode & 0x0F00) >> 8] = internals.delay_timer;
}
#include <stdio.h> // getchar
void Chip8::do_FX0A(uint16_t opcode)
{
    //TODO this should use the api provided to this class
    // (be it sdl or text interfaces)
    std::cout << "press something " <<std::endl;
    int c = getchar();
    //check if key is EOF
    uint8_t cc = static_cast<uint8_t>(c);
    internals.V[(opcode & 0x0F00) >> 8] = cc;
}
void Chip8::do_FX15(uint16_t opcode)
{
    internals.delay_timer = internals.V[(opcode & 0x0F00) >> 8] ;
}
void Chip8::do_FX18(uint16_t opcode)
{
    internals.sound_timer = internals.V[(opcode & 0x0F00) >> 8] ;
}
void Chip8::do_FX1E(uint16_t opcode)
{
    internals.I += internals.V[(opcode & 0x0F00) >> 8] ;
    //might need to have some overflow check here and set vf?
}
void Chip8::do_FX29(uint16_t opcode)
{
    internals.I = internals.memory[ 0x50 + (internals.V[(opcode & 0x0F00) >> 8] * 5)];
}
void Chip8::do_FX33(uint16_t opcode)
{
    uint8_t X = (opcode & 0x0F00) >> 8;

    internals.memory[internals.I] = internals.V[X]  / 100;
    internals.memory[internals.I + 1] = (internals.V[X] % 100) / 10;
    internals.memory[internals.I + 2] = (internals.V[X] / 10) % 10;
}
void Chip8::do_FX55(uint16_t opcode)
{
    /* std::copy(&internals.V[0], &internals.V[((opcode & 0x0F00) >> 8)], */
    std::copy(&internals.V[0], &internals.V[0] + ((opcode & 0x0F00) >> 8),
            &internals.memory[internals.I]);
}
void Chip8::do_FX65(uint16_t opcode)
{
    std::copy(&internals.memory[internals.I], &internals.memory[internals.I] + ((opcode & 0x0F00) >> 8),
            &internals.V[0]);
}

void Chip8::dump_internals()
{
    //this should go to file or terminal or gui based on visual interface set
    // this should also be inthe interface implementation
    std::stringstream output;

    output << "\n";
    output << "keys [" << std::bitset<16>(internals.key) << "]\n";
    output << "I    [" << std::hex << internals.I << "]\n";
    output << "pc   [" << std::hex << internals.pc << "]\n";
    output << "sp   [" << std::hex << internals.sp << "]\n";
    output << "dt   [" << static_cast<uint16_t>(internals.delay_timer) << "]\n";
    output << "st   [" << static_cast<uint16_t>(internals.sound_timer) << "]\n";
    for(int i = 0; i < internals.V.size(); i++)
        output << "V[" << i << "] [" 
               << std::setfill('0') << std::setw(2) << std::hex
               << static_cast<uint16_t>(internals.V[i]) << "]\n";
    for(int i = 0; i < internals.stack.size(); i++)
        output << "S[" << i << "] ["
               << std::setfill('0') << std::setw(2) << std::hex
               << static_cast<uint16_t>(internals.stack[i]) << "]\n";

    output << "Memory";
    for(int i = 0; i < internals.memory.size(); i++)
    {
        if( i % 40 == 0)
            output << "\n" << std::setfill('0') << std::setw(4) << i << " ";
        output << std::setfill('0') << std::setw(2) << std::dec
               << static_cast<uint16_t>(internals.memory[i]);
    }

    output << "\nGraphics";
    for(int i = 0; i < internals.gfx.size(); i++)
    {
        if(i % 64 == 0)
            output << "\n" << std::setfill('0') << std::setw(4) << i << " ";
        output << std::setfill('0') << std::setw(2) << std::hex
               << static_cast<uint16_t>(internals.gfx[i]);
    }

    /* output << "\nGraphics at a glance"; */
    /* for(int i =0 ; i <internals.gfx.size(); i++) */
    /* { */
    /*     if( (i % 64) == 0) */
    /*         output << "\n" << std::setfill('0') << std::setw(4) << i << " "; */
    /*     if (internals.gfx[i]) */
    /*         output << "█"; */
    /*     else */
    /*         output << "."; */
    /* } */
    /* output << "\n"; */

    std::cout << output.str();


}

}


