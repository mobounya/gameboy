#include <cstdint>
#include <iostream>
#include "./Z80_CPU.h"

void print_registers(Z80_CPU cpu)
{
    std::cout << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "A : " << (int)cpu.AF.hi << " | F: " << (int)cpu.AF.lo << std::endl;
    std::cout << "B : " << (int)cpu.BC.hi << " | C: " << (int)cpu.BC.lo << std::endl;
    std::cout << "D : " << (int)cpu.DE.hi << " | E: " << (int)cpu.DE.lo << std::endl;
    std::cout << "H : " << (int)cpu.HL.hi << " | L: " << (int)cpu.HL.lo << std::endl;
    std::cout << "SP : " << (int)cpu.SP.value << " | PC: " << (int)cpu.PC.value << std::endl;
    std::cout << "ABS_ADDR : " << (int)cpu.abs_addr << " | REL_ADDR: " << (int)cpu.rel_addr << std::endl;
    std::cout << "DATA : " << (int)cpu.data << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << std::endl;
}

bool exec_opcode(Z80_CPU cpu, int opcode) {
    auto search_r_r = cpu.opcodes_ld_r_r.find(opcode);
    if (search_r_r != cpu.opcodes_ld_r_r.end()) {
        std::cout << "Hello From REGISTER TO REGISTER" << std::endl;
        cpu.LD_8BIT_REGISTER_TO_8BIT_REGISTER((search_r_r->second).reg1, (search_r_r->second).reg2);
        return true;
    }
    auto search_r_n = cpu.opcodes_ld_r_n.find(opcode);
    if (search_r_n != cpu.opcodes_ld_r_n.end()) {
        std::cout << "Hello From IMMEDIATE DATA TO REGISTER" << std::endl;
        cpu.LD_IMMEDIATE_8BIT_DATA_TO_8BIT_REGISTER(search_r_n->second);
        return true;
    }
    return false;
}

int main(void)
{
    int  opcode;
    Z80_CPU cpu;

    cpu.AF.hi = 42;
    cpu.AF.lo = 43;
    cpu.BC.hi = 44;
    cpu.BC.lo = 45;
    cpu.DE.hi = 46;
    cpu.DE.lo = 47;
    cpu.HL.hi = 48;
    cpu.HL.lo = 49;
    while (1) {
        print_registers(cpu);
        std::cout << "Enter the opcode in Hexadecimal: ";
        std::cin >> std::hex >> opcode;
        std::cout << std::endl;
        std::cout << "Opcode entered: " << opcode << std::endl;
        
        if (!exec_opcode(cpu, opcode)){
            std::cout << "Not implemented yet!!!" << std::endl;
        }
    }
    return 0;
}