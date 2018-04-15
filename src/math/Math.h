#pragma once
#define M_PI       3.14159265358979323846

namespace Math {
	template<typename T>
	T ToRadian(const T t)
	{
		return(M_PI*t / (T)180);
	}

}