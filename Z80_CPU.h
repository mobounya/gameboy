#ifndef Z80_CPU_H
#define Z80_CPU_H

#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <map>

class Z80_CPU
{
public:
    Z80_CPU();
    ~Z80_CPU();
	
	// opcodes stucts
	struct R8_R8 {
		int8_t	&reg1;
		int8_t	&reg2;
	};

	// opcodes maps
	std::map<int8_t, R8_R8> opcodes_ld_r_r { 
		{0x40, {B, B}}, {0x41, {B, C}}, {0x42, {B, D}}, {0x43, {B, E}}, {0x44, {B, H}}, {0x45, {B, L}}, {0x47, {B, A}}, {0x48, {C, B}}, {0x49, {C, C}}, {0x4A, {C, D}}, {0x4B, {C, E}}, {0x4C, {C, H}}, {0x4D, {C, L}}, {0x4F, {C, A}}, 
		{0x50, {D, B}}, {0x51, {D, C}}, {0x52, {D, D}}, {0x53, {D, E}}, {0x54, {D, H}}, {0x55, {D, L}}, {0x57, {D, A}}, {0x58, {E, B}}, {0x59, {E, C}}, {0x5A, {E, D}}, {0x5B, {E, E}}, {0x5C, {E, H}}, {0x5D, {E, L}}, {0x5F, {E, A}}, 
		{0x60, {H, B}}, {0x61, {H, C}}, {0x62, {H, D}}, {0x63, {H, E}}, {0x64, {H, H}}, {0x65, {H, L}}, {0x67, {H, A}}, {0x68, {L, B}}, {0x69, {L, C}}, {0x6A, {L, D}}, {0x6B, {L, E}}, {0x6C, {L, H}}, {0x6D, {L, L}}, {0x6F, {L, A}}, 
		{0x78, {A, B}}, {0x79, {A, C}}, {0x7A, {A, D}}, {0x7B, {A, E}}, {0x7C, {A, H}}, {0x7D, {A, L}}, {0x7F, {A, A}}, 
	};


	// 8-bit instructions
	void LD_FROM_REGISTER_TO_REGISTER(int8_t &reg1, int8_t &reg2);
	void LD_B_n();
	void LD_B_HL();
	void LD_A_nn();

	// Helpers
	void fetch();

	// My totally legit ram
	std::array<int8_t, 2048> ram;
	void	write(int16_t address, int8_t data);
	int8_t 	read(int16_t address);

	enum REGISTER_ACCESS_MODE {
		READ,
		WRITE
	};

	// Addressing Modes
	void IMMEDIATE();
	void INDIRECT_REGISTER_HL();
	void INDIRECT_REGISTER_DE();
	void EXTENDED_ADDR();
	void RELATIVE_ADDR();
	void WR_REGISTER(REGISTER_ACCESS_MODE type, int8_t &reg);

    // Registers
	int8_t A = 0x00; // A = Accumulator
	int8_t F = 0x00; // F = flags

	int8_t B = 0x00;
	int8_t C = 0x00;

	int8_t D = 0x00;
	int8_t E = 0x00;

	int8_t H = 0x00;
	int8_t L = 0x00;

	int16_t SP = 0x00; // Stack Pointer
	int16_t PC = 0x00; // Program Counter/Pointer

	int16_t abs_addr = 0x00;
	int8_t  rel_addr = 0x00;

	int8_t data = 0x00;
};

#endif