// FILE_Prac01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <conio.h>

unsigned int WriteToFile(const char* Filename, const char* String);
unsigned int ReadFromFile(const char* Filename, char** ppMem); 


int main()
{
    char* pStr = nullptr;

    char Str[] = "Hello World!";
    const char* FileName = "abc.txt";

    // Write File
    unsigned int WrittenBytes = WriteToFile(FileName,Str); 
    printf("Wrote string in file named %s and sized %u bytes\n", FileName,WrittenBytes);

    // Read File 
    unsigned int ReadBytes = ReadFromFile(FileName, (char**)&pStr);

    printf("%u b file has a string %s\n", ReadBytes,pStr);
    free(pStr);
    _getch();
}

unsigned int WriteToFile(const char* Filename, const char* String)
{
    unsigned int WrittenBytes = 0;
    FILE* dest = nullptr;
    fopen_s(&dest, Filename, "wb");

    if (nullptr == dest)
    {
        return 0;
    }
    long oldpos = ftell(dest);


    unsigned int len = (unsigned int)strlen(String);
    fwrite(&len, sizeof(unsigned int),1,dest); // Write header
    fwrite(String, sizeof(char), len, dest); // Write body(String)
    
    long curpos = ftell(dest);
    WrittenBytes = curpos - oldpos;
    fclose(dest);
    return WrittenBytes;
}

unsigned int ReadFromFile(const char* Filename, char** ppMem)
{
    FILE* src = nullptr;
    fopen_s(&src, Filename, "rb");
    if (nullptr == src)
    {
        return 0;
    }
    unsigned int oldpos = ftell(src);
    // Read header
    unsigned int len = 0; 
    fread(&len, sizeof(unsigned int), 1, src);

    // Read body
    char* String = (char*)malloc(len+1);
   
    fread(String, sizeof(char), len, src);
    String[len] = 0;

    unsigned int curpos = ftell(src);

    unsigned int ReadBytes = curpos - oldpos;
    *ppMem = String;
    fclose(src);
    return ReadBytes;
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
