#include <iostream>
#include "BUS.h"
#include "RAM.h"

int main(void)
{
    BUS mybus;
    RAM myram;

    mybus.registerMapping({0xC000, 0x0, 0xFFF, myram}); // 4 Kib Work RAM
    mybus.registerMapping({0xD000, 0x1000, 0xFFF, myram}); // 4 Kib Work RAM (not switchable yet)
    mybus.registerMapping({0xE000, 0x0, 0x1DFF, myram}); // ECHO RAM

    int8_t value_read;

    std::cout << (int)mybus.read(0xc000) << std::endl;
    mybus.write(0xC001, 69);
    std::cout << (int)mybus.read(0xc001) << std::endl;

    // Contaminated Bus Test
    std::cout << (int)mybus.read(0x0) << std::endl;
    return (0);
}