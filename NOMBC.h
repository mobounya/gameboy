#ifndef NOMBC_H
#define NOMBC_H
#include "CARTIDGE.h"

class NOMBC : public CARTIDGE::MBC
{
public:
    int getRealRead(uint16_t addr);
    int getRealWrite(uint16_t addr, int8_t data);
};

#endif