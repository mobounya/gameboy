#include "BUS.h"
#include <iostream>

BUS::BUS()
{

}

BUS::~BUS()
{

}

void    BUS::write(uint16_t addr, int8_t data)
{
    int32_t offset;
    BUS::ADDR_MAP *map = this->getMappingForAddr(addr);
    if (map)
    {
        offset = addr - map->virtStart;
        map->device.busWrite(offset, data);
    }
}

int8_t  BUS::read(uint16_t addr)
{
    int32_t offset;
    BUS::ADDR_MAP *map = this->getMappingForAddr(addr);
    if (map)
    {
        offset = addr - map->virtStart;
        this->data = map->device.busRead(offset);
    }
    return (this->data);
}

BUS::ADDR_MAP *BUS::getMappingForAddr(uint16_t addr)
{
    int32_t offset;

    for (int i = 0; i < this->mappings.size(); i++)
    {
        BUS::ADDR_MAP *map = &(this->mappings[i]);

        offset = (int32_t)addr - (int32_t)map->virtStart;
        if (offset >= 0 && offset <= map->size)
            return (map);
    }
    return (NULL);
}

void    BUS::registerMapping(BUS::ADDR_MAP mapping)
{
    this->mappings.push_back(mapping);
}

void BUS_DEVICE::busWrite(uint16_t addr, int8_t data)
{
    return ;
}

int8_t  BUS_DEVICE::busRead(uint16_t addr)
{
    return (69);
}