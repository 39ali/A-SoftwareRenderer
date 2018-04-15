#pragma once
#include "Vector4.h"
#include "Math.h"

namespace Math {

	template<typename T>
	class Matrix44
	{
	public:
		Matrix44() {};
		Matrix44 operator*(const Matrix44& m)
		{
			Matrix44 c;
			for (uint8_t i = 0; i < 4; i++)
			{
				for (uint8_t j = 0; j < 4; j++)
				{
					c[i][j] = mat[i][0] * m[0][j] + mat[i][1] * m[1][j] + mat[i][2] * m[2][j] + mat[i][3] * m[3][j];
				}

			}

		};

		Vector4<T> operator*(const Vector4<T>& v)const
		{
			Vector4<T> u;
			u.x = mat[0][0] * v.x + mat[0][1] * v.y + mat[0][2] * v.z + mat[0][3] * v.w;
			u.y = mat[1][0] * v.x + mat[1][1] * v.y + mat[1][2] * v.z + mat[1][3] * v.w;
			u.z = mat[2][0] * v.x + mat[2][1] * v.y + mat[2][2] * v.z + mat[2][3] * v.w;
			u.x = mat[3][0] * v.x + mat[3][1] * v.y + mat[3][2] * v.z + mat[3][3] * v.w;

			return u;
		}

		void Identity()
		{
			for (uint8_t i = 0; i < 4; i++)
			{
				for (uint8_t j = 0; j < 4; j++)
				{
					if (i == j)
						mat[i][j] = 1;
					else
						mat[i][j] = 0;
				}
			}
		};



		void Perspective(T fov, T far, T near, T aspectRatio)
		{
			Identity();
			T fovdiv2 = Math::ToRadian(fov) / (T)2;
			T tanOver1 = (T)1 / std::tan(fovdiv2);
			T farMinusNear = (far - near);

			mat[0][0] = ((T)1 / aspectRatio) *tanOver1;
			mat[1][1] = tanOver1;
			mat[2][2] = -(far + near) / farMinusNear;
			mat[2][3] = -(T)2 * (far*near) / (farMinusNear);
			mat[3][3] = 0;
			mat[3][2] = -(T)1;
		}

		T* operator[](uint8_t i)
		{
			return mat[i];
		}


		/*const T* operator[](uint8_t i)
		{
			return mat[i];
		}*/

	private:
		T mat[4][4];
	};

	typedef Matrix44<float> mat44f;
}