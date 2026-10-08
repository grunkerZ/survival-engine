#pragma once
#ifndef __ENGINE_H__
#define __ENGINE_H__
#include "AssetManager.h"
#include "Upgrades.h"
#include "ECS.h"
#include <map>
#include <utility>
#include <SDL_ttf.h>

const int SCREEN_W = 1366;
const int SCREEN_H = 768;
const int CELL_SIZE = 64;
const int CHUNK_SIZE = 10;
const int MAX_SLOTS = 6;

struct ChunkPrefab {
	int tiles[CHUNK_SIZE][CHUNK_SIZE];
};

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
	int pendingUpgrades = 0;
	float maxFireCooldown = 1.0f;
	float waveCooldown = 0.0f;
	float difficulty = 1.0f;
	float enemyAmount = 0.0f;
	bool paused = false;
	int inventoryLevels[ITEM_MAX] = { 0 };
	int currentWeaponCount = 0;
	int currentPassiveCount = 0;
	float playerSpeed = 100.0f;
	int playerDamage = 1;
	float playerArea = 1.0f;
	int playerAmount = 0;
	float playerCooldownMod = 1.0f;
	std::vector<ItemID> currentUpgradeChoices;
	ActiveWeapon equippedWeapons[MAX_SLOTS];
};

struct WorldData {
	Registry registry;
	std::map<std::pair<int, int>, std::vector<int>> spatialGrid;
	std::vector<ChunkPrefab> availablePrefabs;
	std::map<std::pair<int, int>, int> loadedChunks;
	Transform camera;
	std::vector<CollisionEvent> collisionEvents;
	Item items[ITEM_MAX];
};

#endif //__ENGINE_H__