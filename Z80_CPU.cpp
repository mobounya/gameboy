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
	Instructions
*/

/*
	Load to 8-bit register from another 8-bit register.
*/

void Z80_CPU::LD_8BIT_REGISTER_TO_8BIT_REGISTER(int8_t &reg1, int8_t &reg2)
{
	WR_REGISTER(REGISTER_ACCESS_MODE::READ, reg2);
	WR_REGISTER(REGISTER_ACCESS_MODE::WRITE, reg1);
}

/*
	Load to 8-bit register 8-bit immediate data. 
*/

void Z80_CPU::LD_IMMEDIATE_8BIT_DATA_TO_8BIT_REGISTER(int8_t &reg)
{
	IMMEDIATE();
	fetch();
	WR_REGISTER(REGISTER_ACCESS_MODE::WRITE, reg);
}

/*
	Load to the 8-bit register r, data from the absolute address specified by the 16-bit register HL.
*/

void Z80_CPU::LD_ABS_ADDR_FROM_HL_TO_8BIT_REGISTER(int8_t &reg)
{
	INDIRECT_REGISTER_HL();
	fetch();
	WR_REGISTER(REGISTER_ACCESS_MODE::WRITE, reg);
}

/*
	Load to the absolute address specified by the 16-bit register HL, data from the 8-bit register r.
*/

void Z80_CPU::LD_8BIT_REGISTER_TO_ABS_ADDR_FROM_HL(int8_t &reg)
{
	INDIRECT_REGISTER_HL();
	WR_REGISTER(REGISTER_ACCESS_MODE::READ, reg);
	write(abs_addr, data);
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
