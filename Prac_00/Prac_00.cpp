// Prac_00.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include "math.h"
#include <math.h>
int main()
{
	//std::cout << "Hello World!\n";
	int  c = Add(1, 2);
	int  d = Sub(1, 2);
	int  f = Mul(2, 3);
	int g = Div(2, 1);
	float h = Sqt(2.0f);
	int j = Pow(2, 3);
	printf("%d %d %d %d\n", c, d, f, g);
	printf("Hello world\n");
	printf("Hello world\n");
	_getch();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to Add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to Add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
