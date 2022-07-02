#ifndef CARTIDGE_H
#define CARTIDGE_H

#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <map>
#include <fstream>
#include <iostream>

class CARTIDGE
{
public:
    CARTIDGE(std::string filename);
    ~CARTIDGE();

    struct HEADER
    {
        uint8_t paddding[0x100];
        uint8_t entryPoint[0x4];
        uint8_t nintendoLogo[0x30];
        // union
        // {
        // uint8_t oldTitle[0xf];
        // struct
        // {
        uint8_t newTitle[0xb];
        uint8_t manufCode[0x4];
        // } __attribute__((packed));
        // };
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
};

#endif