#pragma once
#include "Precompiled.h"
using namespace sf;
template <typename T>
class Vector2Ext : public sf::Vector2<T>
{
public:
	Vector2Ext(Vector2<T>);
	Vector2Ext(T X, T Y);
	~Vector2Ext();
	template <typename T>
	float magnitude();
};

typedef Vector2Ext<float> Vector2Extf;
