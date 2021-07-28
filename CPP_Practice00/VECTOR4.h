#pragma once

struct VECTOR4
{

	float x;
	float y;
	float z;
	float w;

	void Init();
public:
	static VECTOR4 add(const VECTOR4* vect1, const VECTOR4* vect2);
	static VECTOR4 add(const VECTOR4* vect1, const VECTOR4* vect2,const VECTOR4* vect3);
	
	VECTOR4 operator +(const VECTOR4& v) const
 	{
		VECTOR4 r;
		r.x = this->x + v.x;
		r.y = this->y + v.y;
		r.z = this->z + v.z;
		r.w = this->w + v.w;
		return r;
	}
};


