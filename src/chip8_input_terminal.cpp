#include "chip8_input_terminal.h"
#include <termios.h>
#include <stdio.h>
#include <iostream>
#include <thread>

#include <fcntl.h>

//TODO this class should only fetch a keypress then return a value
//for the array index that chip8 should mark as a key pressed
//so chip8.h needs a definition of mapping of what each key pressed means
//
//TODO could use ncurses to poll keys as well


namespace chip8{

namespace {

std::unordered_map<int, int> keypad = {
    {'x',0}, // 1
    {'1',1},
    {'2',2},
    {'3',3},
    {'q',4},
    {'w',5},
    {'e',6},
    {'a',7},
    {'s',8},
    {'d',9},
    {'z',10},
    {'c',11},
    {'4',12},
    {'r',13},
    {'f',14},
    {'v',15},
};

int keys_pressed[16] = {0};


    // TODO put this in the class, per class instance
struct termios old_settings, new_settings;

/* Initialize new terminal i/o settings */
// so you dont need to press enter to get read from terminal
void init_termios(bool echo)
{
    /* fcntl(0, F_SETFL, O_NONBLOCK); */
    tcgetattr(0, &old_settings); /* grab old terminal i/o settings */
    new_settings = old_settings; /* make new settings same as old settings */
    new_settings.c_lflag &= ~ICANON; /* disable buffered i/o */
    if (echo) {
        new_settings.c_lflag |= ECHO; /* set echo mode */
    } else {
        new_settings.c_lflag &= ~ECHO; /* set no echo mode */
    }
    tcsetattr(0, TCSANOW, &new_settings); /* use these new terminal i/o settings now */
}


void reset_termios(void)
{
    tcsetattr(0, TCSANOW, &old_settings);
}

void read_keys(uint8_t *keys){
    // while !stop_reading_keys
    while(true)
    {
        char c = getchar();
        int array_index = keypad[static_cast<uint8_t>(c)];
        keys_pressed[array_index] = 1;
        keys[array_index] = 1;
        /* std::cout << "Got press, index:" << c <<", " << array_index <<std::endl; */
    }
}

} // anon namespace

Chip8InputTerminal::Chip8InputTerminal(Chip8Internals &chip8_internals) : Chip8Input(chip8_internals)
/* Chip8InputTerminal::Chip8InputTerminal(const Chip8Internals &chip8_internals) : Chip8Input(chip8_internals) */
{
    init_termios(false);
    std::thread t(read_keys, std::ref(chip8_internals.key));
    t.detach();
}

Chip8InputTerminal::~Chip8InputTerminal(){
    reset_termios();
}

// TODO MAJOR: throw this in a thread
int Chip8InputTerminal::read_keypress(){
    //TODO sreamline
    /* int key = 0; */
    char c = getchar();
    int array_index = keypad[static_cast<uint8_t>(c)];
    /* key = static_cast<uint8_t>(array_index); */

    //TODO only the Chip8System should be able to read the key
    //so the input/output is readable by the system,
    //then the system updates the chip8 data
    chip8_internals.key[array_index] = 1;
    /* std::cout << "Got press, index:" << c <<", " << array_index <<std::endl; */

    return 0;
}

void Chip8InputTerminal::clear_keypress(){
    for(int i=0; i < 16; i++)
    {
        chip8_internals.key[i] = 0;
        keys_pressed[i] = 0;
    }
}

}
