#include "utils.h"
#include <string>
#include <iostream>

namespace chip8 {

std::string string_to_hex(const std::string& input)
{
    static const char* const hexes = "0123456789ABCDEF";
    size_t len = input.length();
    std::string output;
    output.reserve(2 * len);

    for(size_t i = 0; i < len; i++)
    {
        const unsigned char c = input[i];
        output.push_back(hexes[c >> 4]);
        output.push_back(hexes[c & 0xF]);
    }

    return output;
}

}
