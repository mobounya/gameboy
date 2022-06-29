#ifndef BUS_H
# define BUS_H

#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <map>
#include <vector>

class BUS_DEVICE
{
    public:
        virtual void    busWrite(uint16_t addr, int8_t data);
        virtual int8_t  busRead(uint16_t addr);
};

class BUS
{
	public:
		BUS();
		~BUS();

        void    write(uint16_t addr, int8_t data);
        int8_t  read(uint16_t addr);

        struct ADDR_MAP {
            uint16_t     virtStart;
            uint16_t     realStart;
            uint16_t     size;
            BUS_DEVICE  &device;
        };

        void    registerMapping(ADDR_MAP mapping);

	private:
        std::vector<ADDR_MAP>    mappings;
        ADDR_MAP *getMappingForAddr(uint16_t addr);
        int8_t  data;
};
#endif