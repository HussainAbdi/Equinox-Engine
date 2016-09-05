#include "Vector2Ext.h"


template <typename T>
Vector2Ext<T>::Vector2Ext(Vector2<T> vec)
{
	this = vec;
}

template <typename T>
Vector2Ext<T>::Vector2Ext(T X, T Y)
{
	this->x = X;
	this->y = Y;
}

template <typename T>
Vector2Ext<T>::~Vector2Ext()
{
}

/*template<typename T>
inline float Vector2Ext<T>::magnitude()
{
	float mag;
	mag = sqrtf((this->x) ^ 2 + (this->y) ^ 2);
	return mag;
}*/

