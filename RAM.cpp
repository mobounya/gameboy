#include "RAM.h"

RAM::RAM()
{

}

RAM::~RAM()
{

}

int8_t  RAM::busRead(uint16_t addr)
{
    addr &= RAM_SIZE;
    return (this->mem[addr]);
}

void    RAM::busWrite(uint16_t addr, int8_t data)
{
    addr &= RAM_SIZE;
    this->mem[addr] = data;
}