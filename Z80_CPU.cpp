#include "Z80_CPU.h"

Z80_CPU::Z80_CPU(void)
{
	ram.fill(69);

	AF.value = 0x00;
	BC.value = 0x00;
	DE.value = 0x00;
	HL.value = 0x00;
	SP.value = 0x00;
	PC.value = 0x00;
}

Z80_CPU::~Z80_CPU(void)
{

}

void Z80_CPU::fetch()
{
	data = read(abs_addr);
}

// Totally going to return content of address
int8_t Z80_CPU::read(int16_t address)
{
	return ram[69];
}

// Gonna write that data soooo hard
void Z80_CPU::write(int16_t address, int8_t data)
{
	address = data;
}

/*
	Implementation of Addressing modes.
*/

/*
	- Immediate addressing
	- 8-bit data is the next byte of the instruction.
	- call twice to mimic EXTENDED IMMEDIATE if you need the next two 8-bit values.
*/

void Z80_CPU::IMMEDIATE()
{
	abs_addr = PC.value;
	PC.value++;
}

/*
	- Register Indirect Addressing (HL)
	- 16-bit absolute address is in 16-bit register HL.
*/

void Z80_CPU::INDIRECT_REGISTER_HL()
{
	abs_addr = HL.value;
}

/*
	- Register Indirect Addressing (DE)
	- 16-bit absolute address is in 16-bit register DE.
*/

void Z80_CPU::INDIRECT_REGISTER_DE()
{
	abs_addr = DE.value;
}

/*
	- Register Indirect Addressing (BC)
	- 16-bit absolute address is in 16-bit register BC.
*/

void Z80_CPU::INDIRECT_REGISTER_BC()
{
	abs_addr = BC.value;
}

/*
	- Extended addressing
	- 16-bit absolute address is provided in the next two bytes of the instruction
*/

void Z80_CPU::EXTENDED_ADDR()
{
	int8_t hi;
	int8_t lo;

	hi = read(PC.value);
	PC.value++;
	lo = read(PC.value);
	PC.value++;

	abs_addr = (int16_t)hi << 8 | (int16_t)lo;
}

/*
	- Relative addressing
	- 8-bit relative address is in the next byte of the instruction
*/

void Z80_CPU::RELATIVE_ADDR()
{
	rel_addr = read(PC.value);
	PC.value++;
}

/*
	- Register addressing (A)
	- write or read to 8-bit register A
*/

void Z80_CPU::WR_REGISTER(REGISTER_ACCESS_MODE type, int8_t &reg)
{
	if (type == REGISTER_ACCESS_MODE::READ)
		data = reg;
	else if (type == REGISTER_ACCESS_MODE::WRITE)
		reg = data;
}

/*
	End of implementation of access modes.
*/

/*
	8-bit Instructions
*/

/*
	Instruction: LD r, r’
	Description: Load to the 8-bit register r, data from the 8-bit register r’.
	Opcode: 0b01xxxyyy
*/

void Z80_CPU::LD_r_r(int8_t &reg1, int8_t &reg2)
{
	WR_REGISTER(REGISTER_ACCESS_MODE::READ, reg2);
	WR_REGISTER(REGISTER_ACCESS_MODE::WRITE, reg1);
}

/*
	Instruction: LD r, n
	Description: Load to the 8-bit register r, the immediate data n.
	Opcode: 0b00xxx110
*/

void Z80_CPU::LD_r_n(int8_t &reg)
{
	IMMEDIATE();
	fetch();
	WR_REGISTER(REGISTER_ACCESS_MODE::WRITE, reg);
}

/*
	Instruction: LD r, (HL)
	Description: Load to the 8-bit register r, data from the absolute address specified by the 16-bit register HL.
	Opcode: 0b01xxx110
*/

void Z80_CPU::LD_r_ABS_HL(int8_t &reg)
{
	INDIRECT_REGISTER_HL();
	fetch();
	WR_REGISTER(REGISTER_ACCESS_MODE::WRITE, reg);
}

/*
	Instruction: LD (HL), r
	Description: Load to the absolute address specified by the 16-bit register HL, data from the 8-bit register r
	Opcode: 0b01110xxx
*/

void Z80_CPU::LD_ABS_HL_r(int8_t &reg)
{
	WR_REGISTER(REGISTER_ACCESS_MODE::READ, reg);
	INDIRECT_REGISTER_HL();
	write(abs_addr, data);
}

/*
	Instruction: LD (HL), n
	Description: Load to the absolute address specified by the 16-bit register HL, the immediate data n.
	Opcode: 0b00110110
*/

void Z80_CPU::LD_ABS_HL_n(void)
{
	IMMEDIATE();
	fetch();
	INDIRECT_REGISTER_HL();
	write(abs_addr, data);
}

/*
	Instruction: LD A, (BC)
	Description: Load to the 8-bit A register, data from the absolute address specified by the 16-bit register BC.
	Opcode: 0b00001010
*/

void Z80_CPU::LD_A_ABS_BC(void)
{
	INDIRECT_REGISTER_BC();
	fetch();
	WR_REGISTER(REGISTER_ACCESS_MODE::WRITE, AF.hi);
}

/*
	Instruction: LD A, (DE)
	Description: Load to the 8-bit A register, data from the absolute address specified by the 16-bit register (DE).
	Opcode: 0b00001010
*/

void Z80_CPU::LD_A_ABS_DE(void)
{
	INDIRECT_REGISTER_DE();
	fetch();
	WR_REGISTER(REGISTER_ACCESS_MODE::WRITE, AF.hi);
}

/*
	Load to 8-bit register data from absolute address in the next two bytes in the instruction
*/

void Z80_CPU::LD_A_nn()
{
	EXTENDED_ADDR();
	fetch();
	WR_REGISTER(REGISTER_ACCESS_MODE::WRITE, AF.hi);
}
