#include <stdio.h>
#include <conio.h>
#include "VECTOR4.h"
#include "CGameObject.h"
#include <stdlib.h>

//overloading
//연산자 오버로딩
//스태틱 멤버함수
int main()
{
	/*
	VECTOR4 vect1 = { 1,2,3,4 };
	VECTOR4 vect2 = { 1,2,3,4 };
	VECTOR4 vect3 = { 1,2,3,4 };
	
	//VECTOR4 c = res.add(&vect1, &vect2);
	VECTOR4 c = vect1 + vect2 + vect3;
	c.Init();
	printf("%f %f %f %f",c.x, c.y, c.z, c.w);
	*/
	CGameObject* pObj = new CGameObject;
	CGameObject* pObjArray = new CGameObject[2];
	//CGameObject* pObj = (CGameObject*)malloc(sizeof(CGameObject));
	delete pObj;
	delete[] pObjArray;
	_getch();
	return 0;
}
