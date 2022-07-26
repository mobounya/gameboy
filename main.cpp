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

bool exec_opcode(Z80_CPU &cpu, int opcode) {
    auto search_r_r = cpu.opcodes_ld_r_r.find(opcode);
    if (search_r_r != cpu.opcodes_ld_r_r.end()) {
        std::cout << "Hello From REGISTER TO REGISTER" << std::endl;
        cpu.LD_r_r((search_r_r->second).reg1, (search_r_r->second).reg2);
        return true;
    }
    auto search_r_n = cpu.opcodes_ld_r_n.find(opcode);
    if (search_r_n != cpu.opcodes_ld_r_n.end()) {
        std::cout << "Hello From IMMEDIATE DATA TO REGISTER" << std::endl;
        cpu.LD_r_n(search_r_n->second);
        return true;
    }
    auto search_r_hl = cpu.opcodes_ld_r_hl.find(opcode);
    if (search_r_hl != cpu.opcodes_ld_r_hl.end()) {
        std::cout << "Hello From ABS HL TO REGISTER" << std::endl;
        cpu.LD_r_ABS_HL(search_r_hl->second);
        return true;
    }
    auto search_hl_r = cpu.opcodes_ld_hl_r.find(opcode);
    if (search_hl_r != cpu.opcodes_ld_hl_r.end()) {
        std::cout << "Hello From REGISTER TO ABS HL" << std::endl;
        cpu.LD_ABS_HL_r(search_hl_r->second);
        return true;
    }
    auto search_others = cpu.opcodes_others.find(opcode);
    if (search_others != cpu.opcodes_others.end()) {
        std::cout << "Hello From OTHER OPCODES" << std::endl;
        (cpu.*search_others->second)();
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