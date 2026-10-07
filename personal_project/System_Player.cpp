#include "System.h";
#include "MathUtils.h"

void LevelUp(GameState& state) {
	while (state.playerXP >= state.xpToNextLvl) {
		state.playerXP -= state.xpToNextLvl;
		state.playerLvl++;
		state.pendingUpgrades++;
		state.xpToNextLvl *= 1.2f;
	}
}

void PickupResolutionSystem(WorldData& world, GameState& state) {
	for (const auto& event : world.collisionEvents) {
		int xp = -1;
		int player = -1;
		if (world.registry.hasPlayerController[event.entityA] && world.registry.isExperience[event.entityB]) {
			player = event.entityA;
			xp = event.entityB;
		}
		else if (world.registry.hasPlayerController[event.entityB] && world.registry.isExperience[event.entityA]) {
			player = event.entityB;
			xp = event.entityA;
		}

		if (player != -1 && xp != -1) {
			if (!world.registry.isActive[player] || !world.registry.isActive[xp]) continue;
			state.playerXP++;
			world.registry.DestroyEntity(xp);
		}
	}
	LevelUp(state);
}

void MagnetSystem(Registry& registry, int playerId) {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isExperience[i]) {
			float dist = GetDistance(registry.position[i].x, registry.position[i].y, registry.position[playerId].x, registry.position[playerId].y);
			if (dist < 50) {
				Vector2D dir = GetDirection(registry.position[playerId].x, registry.position[playerId].y, registry.position[i].x, registry.position[i].y);
				registry.position[i].x += (3.0f * dir.x);
				registry.position[i].y += (3.0f * dir.y);
			}
		}
	}
}