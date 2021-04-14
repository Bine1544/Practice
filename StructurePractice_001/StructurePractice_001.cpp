// StructurePractice_001.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <conio.h>
#include <memory.h>
#include "VECTOR3.h"


void Set(VECTOR3* pv3Out, float _x, float _y, float _z)
{
    pv3Out->x = _x;
    pv3Out->y = _y;
    pv3Out->z = _z;
}
void pAdd(VECTOR3* pv3Result, const VECTOR3* pA, const VECTOR3* pB)
{
    pv3Result->x = pA->x + pB->x;
    pv3Result->y = pA->y + pB->y;
    pv3Result->z = pA->z + pB->z;
}
VECTOR3 Add(const VECTOR3* pA, const VECTOR3* pB)
{
    VECTOR3 c;
    c.x = pA->x + pB->x;
    c.y = pA->y + pB->y;
    c.z = pA->z + pB->z;
    return c;
}
void Copy(VECTOR3* pDest, VECTOR3* pSrc)
{
    memcpy(pDest, pSrc, sizeof(VECTOR3));
}
int main()
{
    VECTOR3 a;
    VECTOR3 b;
    a.x = 0;
    a.Set(4.0f, 5.0f, 6.0f);
    b.Set(1.0f, 2.0f, 3.0f);
    a.Add(&b);
    a.Sub(&b);
    a.Mul(&b);
    a.Div(&b);
    //Set(&b, 4.0f, 5.0f, 6.0f);
    //Set(&a, 1.0f, 2.0f, 3.0f);
   // *(&a) = *(&b);
    //copy(&a, &b);
    VECTOR3 c;
    pAdd(&c, &a, &b);
    _getch();
    return 0;
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
