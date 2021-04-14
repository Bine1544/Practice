#include "VECTOR3.h"

void VECTOR3::Add(VECTOR3* src)
{
    x += src->x;
    y += src->y;
    z += src->z;
}
void VECTOR3::Sub(VECTOR3* src)
{
    x -= src->x;
    y -= src->y;
    z -= src->z;
}
void VECTOR3::Mul(VECTOR3* src)
{
    x *= src->x;
    y *= src->y;
    z *= src->z;
}
void VECTOR3::Div(VECTOR3* src)
{
    x /= src->x;
    y /= src->y;
    z /= src->z;
}
void VECTOR3::Set(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}