#ifndef _BMPFONT_H
#define _BMPFONT_H

#include <cstdio>
#include <stdint.h>

typedef struct
{
    char fileHead[4];
    uint32_t fileSize;
    uint8_t sectionNum;
    uint8_t fontHeight;
    uint16_t flag;
    char reserve[4];
}binFileHead;

typedef struct
{
    uint16_t fistChar;
    uint16_t lastChar;
    uint32_t firstAddr;
}binFileSection;

typedef struct
{
    uint32_t offAddr     : 26;
    uint32_t fontWidth   : 6;
}binFileCharInfo;

class BMPFont
{
public:
    BMPFont();
    ~BMPFont();

    bool initFromBinFile(char *fileName);
    bool unicode2bmpfont(wchar_t unicodeChar, __int8 *bmpFontBuffer, int *bmpFontBufferSize, int *bmpFontWidth);

    binFileHead *getbinFileHead(){return &head;}
private:
    FILE *binFile;
    binFileHead head;
    binFileSection *sections;
};

#endif