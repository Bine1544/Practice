// Array00.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <conio.h>
const int MAX_INPUT_COUNT = 5;
//#define MAX_INPUT_COUNT 5

int sum(int* pa, int count);
void scan(int* pa, int count);
int main()
{
    int a[MAX_INPUT_COUNT] = {};
    int* pa = a;
 
    size_t size = sizeof(a);
    //int Count = sizeof(a) / sizeof(int);
    int Count = _countof(a);
    char* p = (char*)pa;
    //*(pa+1) = 1;
    *(p + 4) = 1;

    
    //int b = 0;
    //int c = 0;
    scan(a, Count);
    int s = sum(a, Count);
    printf("%d", s);
    _getch();

}
void scan(int* pa, int count)
{
    for (int i = 0; i < count; i++)
    {
        
        scanf_s("%d", pa);
        pa++;
    }
}
int sum(int* pa, int count)
{
    //pa[0];
    //pa[1];
    //pa[2];
    //pa[3];
    //pa[4];
    //.
    //.
    //.
    // pa[count-1]
    int s = 0;

    for (int i = 0; i < count; i++)
    {
        s += pa[i];
    }

    return s;
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
