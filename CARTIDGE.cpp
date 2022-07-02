#include "CARTIDGE.h"

CARTIDGE::CARTIDGE(std::string filename)
{
    std::fstream file;

    file.open(filename);
    file.read((char *)&this->header, sizeof(CARTIDGE::HEADER));
    file.close();
}

CARTIDGE::~CARTIDGE()
{
}

/*
** DEBUG FUNCTIONS
*/

static void printHex(uint8_t *array, int size)
{
    printf("\t");
    for (int i = 0; i < size; i++)
    {
        if (i % 16 == 0 && i != 0)
            printf("\n\t");
        printf("%2.2hhX ", array[i]);
    }
    printf("\n");
}

static std::string getCartidgeTypeCode(uint8_t type)
{
    switch (type)
    {
    case 0x00:
        return ("ROM ONLY");
    case 0x01:
        return ("MBC1");
    case 0x02:
        return ("MBC1+RAM");
    case 0x03:
        return ("MBC1+RAM+BATTERY");
    case 0x05:
        return ("MBC2");
    case 0x06:
        return ("MBC2+BATTERY");
    case 0x08:
        return ("ROM+RAM");
    case 0x09:
        return ("ROM+RAM+BATTERY");
    case 0x0B:
        return ("MMM01");
    case 0x0C:
        return ("MMM01+RAM");
    case 0x0D:
        return ("MMM01+RAM+BATTERY");
    case 0x0F:
        return ("MBC3+TIMER+BATTERY");
    case 0x10:
        return ("MBC3+TIMER+RAM+BATTERY");
    case 0x11:
        return ("MBC3");
    case 0x12:
        return ("MBC3+RAM");
    case 0x13:
        return ("MBC3+RAM+BATTERY");
    case 0x19:
        return ("MBC5");
    case 0x1A:
        return ("MBC5+RAM");
    case 0x1B:
        return ("MBC5+RAM+BATTERY");
    case 0x1C:
        return ("MBC5+RUMBLE");
    case 0x1D:
        return ("MBC5+RUMBLE+RAM");
    case 0x1E:
        return ("MBC5+RUMBLE+RAM+BATTERY");
    case 0x20:
        return ("MBC6");
    case 0x22:
        return ("MBC7+SENSOR+RUMBLE+RAM+BATTERY");
    case 0xFC:
        return ("POCKET CAMERA");
    case 0xFD:
        return ("BANDAI TAMA5");
    case 0xFE:
        return ("HuC3");
    case 0xFF:
        return ("HuC1+RAM+BATTERY");
    default:
        return ("UNKNOWN");
    }
}

static std::string getRomSize(int8_t size)
{
    switch (size)
    {
    case 0x0:
        return ("32 Kbyte, 2 banks (No ROM banking)");
    case 0x1:
        return ("64 Kbyte, 4 banks");
    case 0x2:
        return ("128 Kbyte, 8 banks");
    case 0x3:
        return ("256 Kbyte, 16 banks");
    case 0x4:
        return ("512 Kbyte, 32 banks");
    case 0x5:
        return ("1 Mbyte, 64 banks");
    case 0x6:
        return ("2 Mbyte, 128 banks");
    case 0x7:
        return ("4 Mbyte, 256 banks");
    case 0x8:
        return ("8 Mbyte, 512 banks");
    case 0x52:
        return ("1.1 Mbyte, 72 banks");
    case 0x53:
        return ("1.2 Mbyte, 80 banks");
    case 0x54:
        return ("1.5 Mbyte, 96 banks");
    default:
        return ("UNKNOWN");
    }
}

static std::string getRamSize(int8_t size)
{
    switch (size)
    {
    case 0x00:
        return ("0, No RAM");
    case 0x01:
        return ("-, Unused");
    case 0x02:
        return ("8 KB, 1 bank");
    case 0x03:
        return ("32 KB, 4 banks of 8 KB each");
    case 0x04:
        return ("128 KB, 16 banks of 8KB each");
    case 0x05:
        return ("64 KB, 8 banks of 8KB each");
    default:
        return ("UNKNOWN");
    }
}

static uint8_t calculateHeaderChecksum(CARTIDGE::HEADER header)
{
    uint8_t sum = 0;
    uint8_t *start;
    uint8_t *end;

    start = (uint8_t *)&header.newTitle;
    end = (uint8_t *)&header.headerChecksum;
    while (start < end)
    {
        sum = sum - *start - 1;
        start++;
    }
    return (sum);
}

void CARTIDGE::debugPrintDetails(void)
{
    CARTIDGE::HEADER header = this->header;
    printf("ENTRY POINT:\n");
    printHex(header.entryPoint, 0x4);
    printf("NINTENDO LOGO :\n");
    printHex(header.nintendoLogo, 0x30);
    printf("TITLE:\n\t`%-11.11s`\n", header.newTitle);
    printHex(header.newTitle, 0xb);
    printf("MANUFACTURER CODE:\n");
    printf("\t`%-4.4s`\n", header.manufCode);
    printHex(header.manufCode, 0x4);
    printf("GCB FLAG:\n\t%2.2X\n", header.gcbFlag);
    if (header.gcbFlag == 0xC0)
        printf("\t(Game works on CGB only)\n");
    else if (header.gcbFlag == 0x80)
        printf("\t(Game supports CGB functions, but also works on old Game Boys)\n");
    printf("NEW LICENSE CODE:\n\t%2.2X%2.2X\n", header.licenseCode[0], header.licenseCode[1]);
    printf("SGB Flag:\n\t%2.2X %s\n", header.sgbFlag, header.sgbFlag == 0x03 ? "(ASupports SGB functions)" : "");
    printf("CARTIDGE TYPE:\n\t%2.2X (%s)\n", header.cartidgeType, getCartidgeTypeCode(header.cartidgeType).c_str());
    printf("ROM SIZE:\n\t%2.2X [%s]\n", header.ROMSize, getRomSize(header.ROMSize).c_str());
    printf("RAM SIZE:\n\t%2.2X [%s]\n", header.RAMSize, getRamSize(header.RAMSize).c_str());
    printf("DESTINATION CODE:\n\t%2.2X", header.destinationCode);
    if (header.destinationCode == 0x0)
        printf(" [Japanese]\n");
    else if (header.destinationCode == 0x01)
        printf(" [Non-Japanese]\n");
    else
        printf(" [Unknown]\n");
    printf("OLD LICENSE CODE:\n\t%2.2X\n", header.oldLicenseCode);
    if (header.oldLicenseCode == 0x33)
        printf("\t(NEW LICENCE CODE IS USED INSTEAD)\n");
    printf("MASK ROM VERSION:\n\t%2.2X\n", header.maskRomVersion);
    printf("HEADER CHECKSUM:\n\t%2.2X ", header.headerChecksum);
    uint8_t hSum = calculateHeaderChecksum(header);
    if (header.headerChecksum == hSum)
        printf("[OK]\n");
    else
        printf("[KO = %2.2X]\n", hSum);
    printf("GLOBAL CHECKSUM:\n\t%4.4x\n", header.globalChecksum);
}