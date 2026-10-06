#include "System.h";
#include "MathUtils.h"

void PickupResolutionSystem(WorldData& world, int& playerXP) {
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
			playerXP++;
			world.registry.DestroyEntity(xp);
		}
	}
}

void MagnetSystem(Registry& registry, int playerId) {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isExperience[i]) {
			float dist = GetDistance(registry.position[i].x, registry.position[i].y, registry.position[playerId].x, registry.position[playerId].y);
			if (dist < 150) {
				Vector2D dir = GetDirection(registry.position[playerId].x, registry.position[playerId].y, registry.position[i].x, registry.position[i].y);
				registry.velocity[i].dx += (1.5f * dir.x);
				registry.velocity[i].dy += (1.5f * dir.y);
			}
		}
	}
}