# Gameboy
A gameboy emulator developed with c++

# Sharp SM83 CPU (based on the Z80)

the gameboy uses the sharp SM83 cpu which is based on the Z80, while we will use the Z80 documentation as a resource, we should keep in mind any differences
they might have

## Adressing modes

### Immediate Addressing

In the immediate addressing mode, the next byte of the instruction contains the operand.

example: `LD B, n` load 8-bit data n to the register B

### Immediate Extended Addressing
 
same as above, the only difference is that **Immediate Extended Addressing** operand is in the next two bytes, please note that we don't have an explicit
implementation of this, we can just use the above addressing mode twice.

example: `LD BC, nn` load 16-bit data nn to 16-bit register BC

### Relative Addressing

Relative addressing uses the next 8-bit signed two’s complement number as an offset to the program counter (PC), the displacement happens at PC + 2,
PC being the opcode, PC + 1 being the operand, displacement happens at PC + 2.

example: `JR e` Unconditional jump to the relative address specified by the signed 8-bit operand e

### Extended Addressing

Extended addressing mode uses the next 2 bytes as an absolute address that you can read, write or jump to.

example: `LD (nn), A` Load to the absolute address specified by the 16-bit operand nn, data from the 8-bit A register.

### Register Addressing

Register addressing uses one or two registers as operands, note that the register(s) is not provided as actual operands but instead it's implied
from the 8-bit bytecode, opcode 0b01111100 is instruction `LD A,H`, the instruction is 1 byte long.

example: `LD A, B` Load 8-bit regiser B to 8-bit regiser A

### Register Indirect Addressing

Register Indirect Addressing uses a 16-bit register to be used as an absolute address, same thing as above, register is provided as part of the opcode
not as a seperate operand.

example: `LD A, (HL)` load data at absolute address in the 16-bit HL register to the 8-bit register A
