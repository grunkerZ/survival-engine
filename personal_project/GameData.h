#pragma once
#ifndef __ENGINE_H__
#define __ENGINE_H__
#include "AssetManager.h"
#include "ECS.h"
#include <map>
#include <vector>
#include <utility>
#include <SDL_ttf.h>

const int SCREEN_W = 1366;
const int SCREEN_H = 768;
const int CELL_SIZE = 64;

struct CollisionEvent {
	int entityA;
	int entityB;
};

struct EngineContext {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool running = true;
	float dt = 0.0f;
	float fpsTimer = 0.0f;
	int frameCount = 0;
	int currentFps = 0;
	AssetManager assets;
	TTF_Font* debugFont = nullptr;
	SDL_Texture* textureMap[ET_END] = { nullptr };
};

struct GameState {
	int playerID = -1;
	int playerXP = 0;
	int playerLvl = 1;
	int xpToNextLvl = 5;
	float fireTimer = 0.0f;
	float maxFireCooldown = 1.0f;
	float waveCooldown = 0.0f;
	float difficulty = 1.0f;
	float enemyAmount = 0.0f;
};

struct WorldData {
	Registry registry;
	std::map<std::pair<int, int>, std::vector<int>> spatialGrid;
	Transform camera;
	std::vector<CollisionEvent> collisionEvents;
};

#endif //__ENGINE_H__
