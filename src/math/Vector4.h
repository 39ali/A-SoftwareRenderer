#pragma once

namespace Math {
	template<typename T >
	class Vector4
	{
	public:
		Vector4(const T x, const T y, const T z, const T w) { this->x = x; this->y = y; this->z = z;  this->w = w; }
		Vector4(const Vector3<T>& v, const T w) { this->x = v.x; this->y = v.y; this->z = v.z;  this->w = w; }
		Vector4() {};
		~Vector4() {};

		Vector4 operator+(const Vector4& v)
		{

			return Vector4(v.x + x, v.y + y, v.z + z);
		}

		Vector4 operator-(const Vector4& v)
		{

			return Vector4(v.x - x, v.y - y, v.z - z);
		}

		Vector4 operator+(const T& t)
		{
			return Vector4(t + x, t + y, t + z);
		}

		Vector4 operator/(const T& t)
		{
			return Vector4(x / t, y / t, z / t);
		}
		Vector4& operator/=(const T& t)
		{
			x /= t; y /= t; z /= t;
			return *this;
		}

		Vector4 operator-()
		{
			return Vector4(-x, -y, -z);
		}

		Vector4& operator*=(const T& t)
		{
			x *= t; y *= t; z *= t;
			return *this;
		}


		operator vec2i() const
		{
			return vec2i(x, y);
		}
		Vector4& operator=(const Vector4& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}


		T  Length()const
		{
			return std::sqrtf(x*x + y * y + z * z);
		}

		void perspectiveDivide()
		{
			x /= w;
			y /= w;
			z /= w;
		};

		Vector4  Normalize()const
		{
			T l = 1 / Length();
			return Vector4(x*l, y*l, z*l);
		}


		T x, y, z, w;
	};


	typedef Vector4<float> vec4f;

}