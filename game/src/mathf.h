#pragma once
#include "raylib.h"

#include <stdlib.h>

inline float GetRandomFloatValue01() 
{
	return rand() / (float)RAND_MAX;
}

inline float GetRandomFloatValue(float min, float max) 
{
	return min + (max - min) * GetRandomFloatValue01();
}

inline Vector2 CreateVector2(float x, float y) 
{
	return (Vector2){ x, y };
}

inline Vector2 GetVector2FromAngle(float angle) 
{
	Vector2 v;
	v.x = cosf(angle);
	v.y = sinf(angle);
	return v;
}