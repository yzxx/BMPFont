#include <cstring>
#include <cstdio>

#include "BMPFont.h"

BMPFont::BMPFont()
{
    binFile = nullptr;
    sections = nullptr;
    memset(&head, 0, sizeof(binFileHead));
}

BMPFont::~BMPFont()
{
    if(binFile)
    {
        fclose(binFile);
        binFile = nullptr;
    }
    if(sections)
    {
        delete[] sections;
        sections = nullptr;
    }
}

bool BMPFont::initFromBinFile(char *fileName)
{
    binFile = fopen(fileName, "rb");
    if(!binFile)
        return false;

    int readSize = 0;
    readSize = fread(&head, sizeof(binFileHead), 1, binFile);
    if(readSize != 1)
        return false;

    sections = new binFileSection[head.sectionNum];
    if(!sections)
        return false;

    readSize = fread(sections, sizeof(binFileSection), head.sectionNum, binFile);
    if(readSize != head.sectionNum)
        return false;

    return true;
}

bool BMPFont::unicode2bmpfont(wchar_t unicodeChar, __int8 *bmpFontBuffer, int *bmpFontBufferSize, int *bmpFontWidth)
{
    int section = -1;

    for(int i = 0; i < head.sectionNum; i++)
    {
        if(unicodeChar >= (sections+i)->fistChar && unicodeChar <= (wchar_t)(sections+i)->lastChar)
        {
            section = i;
            break;
        }
    }

    if(section == -1)
        return false;

    int addr = (sections+section)->firstAddr+(unicodeChar-(sections+section)->fistChar)*sizeof(binFileCharInfo);

    if(fseek(binFile, addr, SEEK_SET))
        return false;

    binFileCharInfo info;
    if(fread(&info, sizeof(binFileCharInfo), 1, binFile) != 1)
        return false;

    if(!info.offAddr)
        return false;

    *bmpFontBufferSize = head.fontHeight*(info.fontWidth+7)/8;
    *bmpFontWidth = info.fontWidth;

    if(fseek(binFile, info.offAddr, SEEK_SET))
        return false;

    if(fread(bmpFontBuffer, *bmpFontBufferSize, 1, binFile) != 1)
        return false;

    return true;
}