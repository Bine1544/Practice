// StructTest_00.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
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
#define WIDTH 2
#define HEIGHT 2


int main()
{
    TGA_HEADER header = {};
    // Load TGA img
    FILE* file;
    
    fopen_s(&file, "aa.tga", "rb"); 
    if (nullptr == file)
    {
        __debugbreak();
    }
    fread(&header, sizeof(header),1,file);
    DWORD SizePerPixel = header.Bits / 8;
    size_t MemSize = header.width * header.height * SizePerPixel;
    PIXEL24* pPixels = (PIXEL24*)malloc(MemSize);
    header.width;
    header.height;
    fread(pPixels, sizeof(PIXEL24), header.width*header.height, file);

    fclose(file);
    // Save TGA img
    
    SetPixel24(pPixels, 2, 2, header.width, header.height);
    fopen_s(&file, "ab.tga", "wb");
    if (nullptr == file)
    {
        __debugbreak();
    }
    fwrite(&header, sizeof(header), 1, file);
    fwrite(pPixels, MemSize, 1, file);
    fclose(file);
    free(pPixels);
    

}
void SetPixel24(PIXEL24* pBits, DWORD x, DWORD y, DWORD width, DWORD height)
{
    DWORD offset = x+y*width;
    PIXEL24* pDest = pBits + offset;
    pDest->r = 255;
    pDest->g = 255;
    pDest->b = 255;

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
