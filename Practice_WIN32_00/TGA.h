#pragma once
typedef unsigned char u_ch;

#include <Windows.h>
#include <stdio.h>
#include <conio.h> 

#pragma pack(push,1)
struct PIXEL24
{
    BYTE r;
    BYTE g;
    BYTE b;
};
#pragma pack(pop)

void SetPixel24(PIXEL24* pBits, DWORD x, DWORD y, DWORD width, DWORD height);
#pragma pack(push,1)
struct TGA_HEADER
{
    char idLength; // 1
    char ColorMapType; // 2
    char ImageType;
    WORD ColorMapFirst;
    WORD ColorMapLast;
    char ColorMapBits;
    WORD FirstX;
    WORD FirstY;
    WORD width;
    WORD height;
    char Bits;
    char Descriptor;
};

#pragma pack(pop)
