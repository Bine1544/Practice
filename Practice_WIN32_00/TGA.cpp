#include "pch.h"
#include "TGA.h"

struct RGBA
{
	BYTE R;
	BYTE G;
	BYTE B;
	BYTE A;

};
DWORD* LoadTGAImage(const char* szFileName, DWORD* pdwOutWidth, DWORD* pdwOutHeight)
{
	TGA_HEADER header = {};
	// Load TGA img
	FILE* file = nullptr;

	fopen_s(&file, szFileName, "rb");
	if (nullptr == file)
	{
		__debugbreak();
	}

	fread(&header, sizeof(header), 1, file);
	DWORD SizePerPixel = header.Bits / 8;
	size_t MemSize = header.width * header.height * SizePerPixel;
	PIXEL24* pPixels = (PIXEL24*)malloc(MemSize);
	fread(pPixels, sizeof(PIXEL24), header.width * header.height, file);

	fclose(file);
	// Save TGA img

	DWORD* pBits32 = (DWORD*)malloc(header.width * header.height * 4);
	for (int y = 0; y < header.height; y++)
	{
		for (int x = 0; x < header.width; x++)
		{
			BYTE r = pPixels[y * header.width + x].r;
			BYTE g = pPixels[y * header.width + x].g;
			BYTE b = pPixels[y * header.width + x].b;

			// y = 0, 256
			//
			int inv_Y = header.height - y - 1;
			DWORD* pDest = (pBits32 + x + inv_Y * header.width);
			RGBA* pbColor = (RGBA*)pDest;
			pbColor->B = b;
			pbColor->G = g;
			pbColor->R = r;
			pbColor->A = 255;

			//(b); // b
			//(g<<8) | (b); // | g | b';
			//(r << 16) | (g << 8) | (b); // 0 |  r | g | b;
			//*pDest = (255 << 24) | (r << 16) | (g << 8) | (b); // 255 | r | g | b ;

		



		}
	}
	
	if (pPixels)
	{
		free(pPixels);
		pPixels = nullptr;
	}
	*pdwOutWidth = header.width;
	*pdwOutHeight = header.height;
	return pBits32;
}