#pragma once
class VECTOR3
{
private:
    float x;
    float y;
    float z;
public:
    void Set(float _x, float _y, float _z);
    void Add(VECTOR3* src);
    void Sub(VECTOR3* src);
    void Mul(VECTOR3* src);
    void Div(VECTOR3* src);
};


