#include "VECTOR4.h"

void VECTOR4::Init()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;

}
VECTOR4 VECTOR4::add(const VECTOR4* vect1,const VECTOR4* vect2)
{
	
	VECTOR4 ret;
	ret.x = vect1->x + vect2->x;
	ret.y = vect1->y + vect2->y;
	ret.z = vect1->z + vect2->z;
	ret.w = vect1->w + vect2->w;
	return ret;
}

VECTOR4 VECTOR4::add(const VECTOR4* vect1,const VECTOR4* vect2,const VECTOR4* vect3)
{
	VECTOR4 ret;
	ret.x = vect1->x + vect2->x + vect3->x;
	ret.y = vect1->y + vect2->y + vect3->y;
	ret.z = vect1->z + vect2->z + vect3->z;
	ret.w = vect1->w + vect2->w + vect3->w;
	
	return ret;
}