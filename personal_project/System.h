#pragma once
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "GameData.h"

void PickupResolutionSystem(WorldData& world, GameState& state);
void MagnetSystem(Registry& registry, int playerId);
void PlayerAutoShootSystem(GameState& state, Registry& registry, float dt);
void CombatResolutionSystem(WorldData& world, GameState& state);
void PhysicsSystem(Registry& registry, float dt);
void PlayerInputSystem(Registry& registry, GameState& state);
void CollisionDetectionSystem(WorldData& world);
void SeperationResolutionSystem(WorldData& world);
void RenderSystem(WorldData& world, EngineContext& engine);
void ClearScreen(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void PresentScreen(SDL_Renderer* renderer);
void RenderUI(WorldData& world, EngineContext& engine, Registry& registry, GameState& state, bool debug);
void Quit(EngineContext& engine);
int Init(EngineContext& engine, Uint32 flags);
void ProcessEvent(EngineContext& engine);
void LifeCycleSystem(WorldData& world);
void UpdateSpatialGrid(WorldData& world);
void EnemyAISystem(Registry& registry);
void EnemySpawnerSystem(WorldData& world, GameState& state, float dt);
void InitMapPrefabs(WorldData& world);
void LoadMapPrefab(WorldData& world, std::string filepath);
void UpdateMapSystem(WorldData& data);
void LevelUp(GameState& state);
void InitUpgrades(WorldData& world);
std::vector<ItemID> RollUpgrades(GameState& state, WorldData& world);
void RenderUpgradeMenu(WorldData& world, GameState& state, EngineContext& engine);

#endif // __SYSTEM_H__