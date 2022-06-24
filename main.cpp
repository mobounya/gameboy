#include <cstdint>
#include <iostream>
#include "./Z80_CPU.h"

int main(void)
{
    Z80_CPU cpu;

    cpu.C = 42;
    cpu.LD_B_C();

    std::cout << (int)cpu.B << std::endl;

    cpu.LD_B_HL();
    std::cout << (int)cpu.B << std::endl;

    cpu.B = 0;
    cpu.LD_B_n();

    std::cout << (int)cpu.B << std::endl;
    return 0;
}