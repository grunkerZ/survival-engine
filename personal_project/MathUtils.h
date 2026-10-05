#pragma once
#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__

#include <cmath>
#include "ECS.h"

struct Vector2D {
	float x, y;
};

inline float GetMagnitude(float x, float y) {
	return sqrt((pow(x, 2) + pow(y, 2)));
}

inline void Normalize(float& x, float& y) {
	float magnitude = GetMagnitude(x, y);
	if (magnitude == 0.0f) return;

	x = x / magnitude;
	y = y / magnitude;
}

inline float GetDistanceSq(float x1, float y1, float x2, float y2) {
	return pow((x1 - x2), 2) + pow((y1 - y2), 2);
}

inline Vector2D GetDirection(float x1, float y1, float x2, float y2) {
	Vector2D dir;

	dir.x = x1 - x2;
	dir.y = y1 - y2;
	
	Normalize(dir.x, dir.y);
	return dir;
}



#endif //__MATHUTILS_H__