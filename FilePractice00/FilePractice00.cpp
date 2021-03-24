// FilePractice00.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
bool WriteText(const char* FileName, const char* Text);
bool ReadText(const char* FileName, char* pOutBuffer, int BufferCount);
long GetFileSize(const char* FileName);

int main()
{
    char text[128] = {};

    long size = GetFileSize("abc.txt");
    printf("size:%d", size);
    const size_t SIZE100M = (1024 * 1024) * 100;
    //char buf[SIZE100M];
    char* pBuffer = (char*)malloc(SIZE100M);
       

   // WriteText("abc.txt","Hello World!");
  //  ReadText("abc.txt", text, _countof(text));
    _getch();
    return 0;
}

bool ReadText(const char* FileName, char* pOutBuffer,int BufferCount)
{
    bool res = false;
    FILE* file = NULL;
    errno_t ret = fopen_s(&file, FileName, "rt");
    if (ret)
    {
        return res;
    }
    fgets(pOutBuffer, BufferCount, file);
    //fscanf_s(file, "%s", pOutBuffer, BufferCount);
    fclose(file);
}
long GetFileSize(const char* FileName)
{
    errno_t res;
    FILE* file = nullptr;
    res = fopen_s(&file, FileName, "rt");
    long loc = 0;
    if (!res)
    {
        fseek(file, 0, SEEK_END);
        loc = ftell(file);
        fclose(file);
    }

    return loc;
}
bool ReadTextAsBinary(const char* FileName, char* pOutBuffer, int BufferCount)
{
    bool res = false;
    FILE* file = NULL;
    errno_t ret = fopen_s(&file, FileName, "rb");
    if (ret)
    {
        return res;
    }
    fgets(pOutBuffer, BufferCount, file);
    //fscanf_s(file, "%s", pOutBuffer, BufferCount);
    fclose(file);
}

bool WriteText(const char* FileName,const char* Text)
{
    bool res = false;
    FILE* file = NULL;
    errno_t ret = fopen_s(&file, FileName, "wt");
    if (ret)
    {
        return res;
    }
 
	// file 오픈 성공했을 경우 ( ret == 0 )
	fprintf_s(file, Text);
    fclose(file);
    res = true;
    return res;
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
