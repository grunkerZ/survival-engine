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

struct GameEngine {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	float dt;
	bool running = 0;
	float fireCooldown=0.0f;
	float waveCooldown = 0.0f;
	int difficulty = 0;
	int playerXP = 0;
	int playerLvl = 1;
	int xpToNextLvl = 5;
	float maxFireCooldown = 1.0f;
	float fpsTimer = 0.0f;
	int frameCount = 0;
	int currentFps = 0;
	float enemyAmount = 0;


	std::map<std::pair<int, int>, std::vector<int>> spatialGrid;

	Transform camera;

	Registry registry;

	AssetManager assets;

	TTF_Font* debugFont = nullptr;

	int Init(Uint32 flags);

	void ProcessEvent();

	void ClearScreen(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void PresentScreen();

	void Quit();

	void PhysicsSystem(float dt);

	void PlayerInputSystem(float dt);

	void RenderSystem();

	void AutoShootSystem();

	void LifeCycleSystem();

	void CollisionSystem();

	void EnemyAISystem();

	void EnemySpawnerSystem(float dt);

	void UpdateSpatialGrid();
	
	void RenderUI();
};



#endif //__ENGINE_H__
