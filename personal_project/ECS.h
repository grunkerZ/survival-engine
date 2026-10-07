#pragma once
#ifndef  __ECS_H__
#define __ECS_H__

#include <SDL_image.h>

const int MAX_ENTITIES = 4096;

enum EntityType {
	ET_NONE,
	ET_PLAYER,
	ET_GRUNT,
	ET_BULLET,
	ET_XP,
	ET_TILESET,
	ET_END
};

struct Transform {
	float x, y;
};

struct Velocity {
	float dx, dy;
};

struct Registry {
	bool isActive[MAX_ENTITIES];
	bool hasPlayerController[MAX_ENTITIES];
	bool hasAIController[MAX_ENTITIES];
	bool isProjectile[MAX_ENTITIES];
	bool isExperience[MAX_ENTITIES];
	int health[MAX_ENTITIES];
	int entityType[MAX_ENTITIES];
	Transform position[MAX_ENTITIES];
	Velocity velocity[MAX_ENTITIES];
	SDL_Rect bounds[MAX_ENTITIES];
	int activeEntityCount = 0;

	int CreateEntity() {
		for (int i = 0; i < MAX_ENTITIES; i++) {
			if (!isActive[i]) {
				isActive[i] = 1;
				activeEntityCount++;
				return i;
			}
		}
		return -1;
	}

	void DestroyEntity(int id) {
		isActive[id] = 0;
		isProjectile[id] = 0;
		isExperience[id] = 0;
		hasPlayerController[id] = 0;
		hasAIController[id] = 0;
		health[id] = 0;
		position[id] = { 0 };
		velocity[id] = { 0 };
		bounds[id] = { 0 };
		activeEntityCount--;
	}
};

#endif //__ECS_H__