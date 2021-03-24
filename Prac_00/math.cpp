#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math.h"

int Pow(int a, int b)
{
    // a = 2
    // c = 2^0 , c = 1
    // c = 2^1 , c = 2
    // c = 2^2 , c = 4
    // c = 2^3 , c = 8
    
    int d = 1;
    for (int i = 0; i < b; i++)
    {
        // a == 2, 
        // b == 1 , d == 2
        // b == 2 , d == 4
        // b == 3 , d == 8

        d = d * a;
        //d= d* a;
    }
    return d;
}
float Sqt(float a)
{
    float c = sqrtf(a);
    return c;
}
int Div(int a, int b)
{
    int c = a / b;
    return c;
}
int Sub(int a, int b)
{
    int c = a - b;
    return c;
}
int Add(int a, int b)
{
    int c = a + b;
    return c;
}
int Mul(int a, int b)
{
    int c = a * b;
    return c;
}