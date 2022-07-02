#ifndef RAM_H
# define RAM_H
# define RAM_SIZE 32768
#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <map>
#include "BUS.h"

class RAM : public BUS_DEVICE
{
	public:
		RAM();
		~RAM();
        void    busWrite(uint16_t addr, int8_t data);
        int8_t  busRead(uint16_t addr);

	private:
        int8_t  mem[RAM_SIZE];
};
#endif