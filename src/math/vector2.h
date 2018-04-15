#pragma once
namespace Math {
	template<typename T>
	class Vector2
	{
	public:
		Vector2(const T x, const T y) { this->x = x; this->y = y; }
		Vector2() {};
		~Vector2() {};

		Vector2 operator+(const Vector2& v)
		{

			return Vector2(v.x + x, v.y + y);
		}
		Vector2 operator*(const T& t)
		{
			return Vector2(t * x, t * y);
		}

		Vector2 operator+(const T& t)
		{
			return Vector2(t + x, t + y);
		}

		Vector2 operator/(const T& t)
		{
			return Vector2(x / t, y / t);
		}
		Vector2& operator/=(const T& t)
		{
			x /= t; y /= t;
			return *this;
		}

		Vector2& operator*=(const T& t)
		{
			x *= t; y *= t;
			return *this;
		}

		Vector2 static PerspectiveDivide(const Vector2& v)
		{
			return Vector2(v.x, v.y);
		}


		T x, y;
	};

	typedef Vector2<float> vec2f;
	typedef Vector2<int> vec2i;

}