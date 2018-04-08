#pragma once


class Vector3 
{ 
public :
	Vector3(const float x, const float y, const float z) { this->x = x; this->y = y; this->z = z; }
	~Vector3() {};

	Vector3 operator+(const Vector3& v)
	{
	
		return Vector3(v.x+ x, v.y +y , v.z+z);
	}

	Vector3 operator+(const float& t)
	{
		return Vector3(t + x, t+ y,t + z);
	}
	

	

	float x, y, z;
};

typedef Vector3 vec3f;