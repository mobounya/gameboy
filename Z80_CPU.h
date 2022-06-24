#ifndef Z80_CPU_H
#define Z80_CPU_H

#pragma once

#include <cstdint>
#include <string>
#include <array>

class Z80_CPU
{
public:
    Z80_CPU();
    ~Z80_CPU();

	// 8-bit instructions
	void LD_B_C();
	void LD_B_n();
	void LD_B_HL();
	void LD_A_nn();

	// Helpers
	void fetch();
public:

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
	void REGISTER_A(REGISTER_ACCESS_MODE type);
	void REGISTER_F(REGISTER_ACCESS_MODE type);
	void REGISTER_B(REGISTER_ACCESS_MODE type);
	void REGISTER_C(REGISTER_ACCESS_MODE type);

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