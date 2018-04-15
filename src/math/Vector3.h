#pragma once
#include "vector2.h"


namespace Math {

	template<typename T>
	class Vector3
	{
	public:
		Vector3(const T x, const T y, const T z) { this->x = x; this->y = y; this->z = z; }
		Vector3() {};
		~Vector3() {};

		Vector3 operator+(const Vector3& v)
		{

			return Vector3(v.x + x, v.y + y, v.z + z);
		}

		Vector3 operator-(const Vector3& v)
		{

			return Vector3(v.x - x, v.y - y, v.z - z);
		}

		Vector3 operator+(const T& t)
		{
			return Vector3(t + x, t + y, t + z);
		}

		Vector3 operator/(const T& t)
		{
			return Vector3(x / t, y / t, z / t);
		}
		Vector3& operator/=(const T& t)
		{
			x /= t; y /= t; z /= t;
			return *this;
		}

		Vector3 operator-()
		{
			return Vector3(-x, -y, -z);
		}

		Vector3& operator*=(const T& t)
		{
			x *= t; y *= t; z *= t;
			return *this;
		}


		operator vec2i() const
		{
			return vec2i(x, y);
		}
		Vector3& operator=(const Vector3& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}


		Vector3 static Cross(const Vector3& u, const Vector3& v)
		{
			return Vector3(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);
		}

		T static Dot(const Vector3& u, const Vector3& v)
		{
			return  u.x*v.x + u.y*v.y + u.z*v.z;
		}

		T  Length()const
		{
			return std::sqrtf(x*x + y * y + z * z);
		}

		Vector3  Normalize()const
		{
			T l = 1 / Length();
			return Vector3(x*l, y*l, z*l);
		}
		T& operator[](const size_t i) {  return i <= 0 ? x : (1 == i ? y : z); }
		T& operator[](const int i) { return i <= 0 ? x : (1 == i ? y : z); }
		T x, y, z;
	};


	typedef Vector3<float> vec3f;
	typedef Vector3<int> vec3i;

}