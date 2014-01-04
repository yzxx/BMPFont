// BMPFont.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "BMPFont.h"

int _tmain(int argc, _TCHAR* argv[])
{
    BMPFont *bmpFont = new BMPFont();
    bool ret = bmpFont->initFromBinFile("arialuni_U16.bin");
    //bool ret = bmpFont->initFromBinFile("maozedong_U16.bin");
    std::cout << ret << std::endl;

    wchar_t c = _T('¹þ');
    //wchar_t c = 0x66f8;

    int fontHeight = bmpFont->getbinFileHead()->fontHeight;
    char *buffer = new char[fontHeight*fontHeight];
    int bufferSize, width;

    ret = bmpFont->unicode2bmpfont(c, buffer, &bufferSize, &width);
    std::cout << ret << std::endl;

    int bytePerLine = bufferSize/fontHeight;

    for(int i = 0; i < fontHeight; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if((*((buffer+i*bytePerLine)+j/8)>>(7-j%8))&0x01)
                std::cout << "* ";
            else
                std::cout << "  ";
        }
        std::cout << std::endl;
    }

    std::cin >> ret;

	return 0;
}

