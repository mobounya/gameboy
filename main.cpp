#include <cstdint>
#include <iostream>
#include "./Z80_CPU.h"

void print_registers(Z80_CPU cpu)
{
    std::cout << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "A : " << (int)cpu.A << " | F: " << (int)cpu.F << std::endl;
    std::cout << "B : " << (int)cpu.B << " | C: " << (int)cpu.C << std::endl;
    std::cout << "D : " << (int)cpu.D << " | E: " << (int)cpu.E << std::endl;
    std::cout << "H : " << (int)cpu.H << " | L: " << (int)cpu.L << std::endl;
    std::cout << "SP : " << (int)cpu.SP << " | PC: " << (int)cpu.PC << std::endl;
    std::cout << "ABS_ADDR : " << (int)cpu.abs_addr << " | REL_ADDR: " << (int)cpu.rel_addr << std::endl;
    std::cout << "DATA : " << (int)cpu.data << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << std::endl;
}

int main(void)
{
    Z80_CPU cpu;
    int  opcode;

    cpu.A = 42;
    cpu.F = 43;
    cpu.B = 44;
    cpu.C = 45;
    cpu.D = 46;
    cpu.E = 47;
    cpu.H = 48;
    cpu.L = 49;
    while (1) {
        print_registers(cpu);
        std::cout << "Enter the opcode in Hexadecimal: ";
        std::cin >> std::hex >> opcode;
        std::cout << std::endl;
        std::cout << "Opcode entered: " << opcode << std::endl;
        auto search = cpu.opcodes_ld_r_r.find(opcode);
        if (search != cpu.opcodes_ld_r_r.end()) {
            std::cout << "Hello" << std::endl;
            cpu.LD_FROM_REGISTER_TO_REGISTER((search->second).reg1, (search->second).reg2);
            print_registers(cpu);
        } else {
            std::cout << "Not implemented yet!!!" << std::endl;
        }
    }
    return 0;
}