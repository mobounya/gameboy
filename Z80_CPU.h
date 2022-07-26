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
	typedef void (Z80_CPU::*instruction)(void);

	// opcodes stucts
	struct R8_R8 {
		int8_t	&reg1;
		int8_t	&reg2;
	};

	// opcodes maps
	std::map<int8_t, R8_R8> opcodes_ld_r_r  { 
		{0x40, {BC.hi, BC.hi}}, {0x41, {BC.hi, BC.lo}}, {0x42, {BC.hi, DE.hi}}, {0x43, {BC.hi, DE.lo}}, {0x44, {BC.hi, HL.hi}}, {0x45, {BC.hi, HL.lo}}, {0x47, {BC.hi, AF.hi}}, {0x48, {BC.lo, BC.hi}}, {0x49, {BC.lo, BC.lo}}, {0x4A, {BC.lo, DE.hi}}, {0x4B, {BC.lo, DE.lo}}, {0x4C, {BC.lo, HL.hi}}, {0x4D, {BC.lo, HL.lo}}, {0x4F, {BC.lo, AF.hi}}, 
		{0x50, {DE.hi, BC.hi}}, {0x51, {DE.hi, BC.lo}}, {0x52, {DE.hi, DE.hi}}, {0x53, {DE.hi, DE.lo}}, {0x54, {DE.hi, HL.hi}}, {0x55, {DE.hi, HL.lo}}, {0x57, {DE.hi, AF.hi}}, {0x58, {DE.lo, BC.hi}}, {0x59, {DE.lo, BC.lo}}, {0x5A, {DE.lo, DE.hi}}, {0x5B, {DE.lo, DE.lo}}, {0x5C, {DE.lo, HL.hi}}, {0x5D, {DE.lo, HL.lo}}, {0x5F, {DE.lo, AF.hi}}, 
		{0x60, {HL.hi, BC.hi}}, {0x61, {HL.hi, BC.lo}}, {0x62, {HL.hi, DE.hi}}, {0x63, {HL.hi, DE.lo}}, {0x64, {HL.hi, HL.hi}}, {0x65, {HL.hi, HL.lo}}, {0x67, {HL.hi, AF.hi}}, {0x68, {HL.lo, BC.hi}}, {0x69, {HL.lo, BC.lo}}, {0x6A, {HL.lo, DE.hi}}, {0x6B, {HL.lo, DE.lo}}, {0x6C, {HL.lo, HL.hi}}, {0x6D, {HL.lo, HL.lo}}, {0x6F, {HL.lo, AF.hi}}, 
		{0x78, {AF.hi, BC.hi}}, {0x79, {AF.hi, BC.lo}}, {0x7A, {AF.hi, DE.hi}}, {0x7B, {AF.hi, DE.lo}}, {0x7C, {AF.hi, HL.hi}}, {0x7D, {AF.hi, HL.lo}}, {0x7F, {AF.hi, AF.hi}}, 
	};

	std::map<int8_t, int8_t &> opcodes_ld_r_n {
		{0x6, BC.hi}, {0xE, BC.lo}, 
		{0x16, DE.hi}, {0x1E, DE.lo}, 
		{0x26, HL.hi}, {0x2E, HL.lo}, 
		{0x3E, AF.hi}, 
	};

	std::map<int8_t, int8_t &> opcodes_ld_r_hl {
		{0x46, BC.hi}, {0x4E, BC.lo},
		{0x56, DE.hi}, {0x5E, DE.lo},
		{0x66, HL.hi}, {0x6E, HL.lo},
		{0x7E, AF.hi},
	};

	std::map<int8_t, int8_t &> opcodes_ld_hl_r {
		{0x70, BC.hi}, {0x71, BC.lo},
		{0x72, DE.hi}, {0x73, DE.lo},
		{0x74, HL.hi}, {0x75, HL.lo},
		{0x77, AF.hi},
	};

	std::map<int8_t, const instruction> opcodes_others {
		{0x36, &Z80_CPU::LD_ABS_HL_n}, {0x0A, &Z80_CPU::LD_A_ABS_BC},
		{0x1A, &Z80_CPU::LD_A_ABS_DE}, {0x02, &Z80_CPU::LD_ABS_BC_A},
		{0x12, &Z80_CPU::LD_ABS_DE_A}, {0xFA, &Z80_CPU::LD_A_ABS_nn},
		{0xEA, &Z80_CPU::LD_ABS_nn_A}, {0xF2, &Z80_CPU::LDH_A_ABS_C},
		{0xE2, &Z80_CPU::LDH_ABS_C_A}, {0xF0, &Z80_CPU::LDH_A_ABS_n},
		{0xE0, &Z80_CPU::LDH_ABS_n_A}, {0x22, &Z80_CPU::LD_A_ABS_INCREMENT_HL}
	};

	// 8-bit instructions
	void LD_r_r(int8_t &reg1, int8_t &reg2);
	void LD_r_n(int8_t &reg);
	void LD_r_ABS_HL(int8_t &reg);
	void LD_ABS_HL_r(int8_t &reg);
	void LD_ABS_HL_n(void);
	void LD_A_ABS_BC(void);
	void LD_A_ABS_DE(void);
	void LD_ABS_BC_A(void);
	void LD_ABS_DE_A(void);
	void LD_A_ABS_nn(void);
	void LD_ABS_nn_A(void);
	void LDH_A_ABS_C(void);
	void LDH_ABS_C_A(void);
	void LDH_A_ABS_n(void);
	void LDH_ABS_n_A(void);
	void LD_A_ABS_INCREMENT_HL(void);

	// Helpers
	void fetch();
	void set_msb_max_to_abs_addr(int8_t value);

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
	void EXTENDED_ADDR();
	void RELATIVE_ADDR();
	void INDIRECT_REGISTER_HL();
	void INDIRECT_REGISTER_DE();
	void INDIRECT_REGISTER_BC();
	void WR_REGISTER(REGISTER_ACCESS_MODE type, int8_t &reg);

	union REG
	{
		struct
		{	
			int8_t hi;
			int8_t lo;
		};
		int16_t value;
	};

    // Registers
	REG AF;

	REG BC;

	REG DE;

	REG HL;

	REG SP; // stack pointer
	REG PC; // Program Counter/Pointer

	int16_t abs_addr = 0x00;
	int8_t  rel_addr = 0x00;

	int8_t data = 0x00;
};

#endif