// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <math.h>

void QuadEquation(float a, float b, float c, float* pX0, float* pX1);

int main()
{
    
    float a = 1.0f;
    float b = 0.0f;
    float c = -1.0f;
    float X0 = 0.0f;
    float X1 = 0.0f;
    
    QuadEquation(a,b,c,&X0,&X1);
    printf("%f %f\n",X0,X1);
    getchar();
    std::cout << "Hello World!\n";
}

void QuadEquation(float a, float b, float c, float* pX0, float* pX1)
{
    float x0 = 0.0f; 
    float x1 = 0.0f;
    // (-b + sqrt(b*b - 4ac)) / 2a
    float bb = b * b;
    float qac = 4.0f * a * c;
    float neg_b = -1.0f * b;
    float ta = 2.0f * a;

    x0 = (neg_b + sqrt(bb - qac)) / ta;
    x1 = (neg_b - sqrt(bb - qac)) / ta;

    *pX0 = x0;
    *pX1 = x1;
    return;
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
