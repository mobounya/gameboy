#ifndef CARTIDGE_H
#define CARTIDGE_H

#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <map>
#include <fstream>
#include <iostream>
#include "BUS.h"
#include "UNITS.h"

class CARTIDGE : public BUS_DEVICE
{
public:
    CARTIDGE(std::string filename);
    ~CARTIDGE();

    void busWrite(uint16_t addr, int8_t data);
    int8_t busRead(uint16_t addr);

    class MBC
    {
        /*
        ** basically MBC will keep track of which banks are active
        **  and will return real offset into CARTIDGE Memory
        */
    public:
        virtual int getRealRead(uint16_t addr);
        virtual int getRealWrite(uint16_t addr, int8_t data);

    private:
        uint ramSize;
        uint romSize;
    };

    struct HEADER
    {
        uint8_t paddding[0x100];
        uint8_t entryPoint[0x4];
        uint8_t nintendoLogo[0x30];
        uint8_t newTitle[0xb];
        uint8_t manufCode[0x4];
        uint8_t gcbFlag;
        uint8_t licenseCode[0x2];
        uint8_t sgbFlag;
        uint8_t cartidgeType;
        uint8_t ROMSize;
        uint8_t RAMSize;
        uint8_t destinationCode;
        uint8_t oldLicenseCode;
        uint8_t maskRomVersion;
        uint8_t headerChecksum;
        uint16_t globalChecksum;
    } __attribute__((packed));

    void debugPrintDetails(void);

private:
    HEADER header;
    MBC *Controller;
    uint ramSize;
    uint romSize;
    uint8_t *MEM;
    bool parseHeader(void);
    bool allocateMemory(void);
    MBC *initMBC(void);
};

#endif