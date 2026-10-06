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

inline float GetDistance(float x1, float y1, float x2, float y2) {
	return sqrt(GetDistanceSq(x1, y1, x2, y2));
}

inline Vector2D GetDirection(float x1, float y1, float x2, float y2) {
	Vector2D dir;

	dir.x = x1 - x2;
	dir.y = y1 - y2;
	
	Normalize(dir.x, dir.y);
	return dir;
}

inline Vector2D GetRandomOffscreenPosition(Transform camera) {
	Vector2D pos;
	float left = camera.x - 150.0f;
	float right = camera.x + SCREEN_W + 150.0f;
	float top = camera.y - 150.0f;
	float bottom = camera.y + SCREEN_H + 150.0f;

	int edge = rand() % 4;

	if (edge == 0) {
		pos.x = left;
		pos.y = camera.y + rand() % SCREEN_H;
	}
	else if (edge == 1) {
		pos.x = right;
		pos.y = camera.y + rand() % SCREEN_H;
	}
	else if (edge == 2) {
		pos.x = camera.x + rand() % SCREEN_W;
		pos.y = top;
	}
	else if (edge == 3) {
		pos.x = camera.x + rand() % SCREEN_W;
		pos.y = bottom;
	}

	return pos;
}



#endif //__MATHUTILS_H__