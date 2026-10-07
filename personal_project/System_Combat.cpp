#include "System.h"
#include "MathUtils.h"
#include "EntityFactory.h"


void PlayerAutoShootSystem(GameState& state, Registry& registry, float dt) {
	state.fireTimer -= dt;
	if (state.fireTimer <= 0.0f) {
		float px = registry.position[state.playerID].x;
		float py = registry.position[state.playerID].y;

		float minDistance = 99999.0f;
		int targetId = -1;

		for (int i = 0; i < MAX_ENTITIES; i++) {
			if (registry.isActive[i] && registry.hasAIController[i]) {
				float dist = GetDistanceSq(px, py, registry.position[i].x, registry.position[i].y);
				if (dist < minDistance) {
					minDistance = dist;
					targetId = i;
				}
			}
		}

		if (targetId != -1) {
			int bullet = SpawnBullet(registry, px, py);
			if (bullet == -1) {
				return;
			}

			Vector2D dir = GetDirection(registry.position[targetId].x, registry.position[targetId].y, px, py);
			registry.velocity[bullet].dx = dir.x * 250.0f;
			registry.velocity[bullet].dy = dir.y * 250.0f;

			state.fireTimer = state.maxFireCooldown - state.playerCooldownMod;
		}
	}
}

void CombatResolutionSystem(WorldData& world, GameState& state) {
	for (const auto& event : world.collisionEvents) {
		int bullet = -1;
		int grunt = -1;

		if (world.registry.isProjectile[event.entityA] && world.registry.hasAIController[event.entityB]) {
			bullet = event.entityA;
			grunt = event.entityB;
		}
		else if (world.registry.isProjectile[event.entityB] && world.registry.hasAIController[event.entityA]) {
			bullet = event.entityB;
			grunt = event.entityA;
		}

		if (bullet != -1 && grunt != -1) {
			if(!world.registry.isActive[bullet] || !world.registry.isActive[grunt]) continue;
			world.registry.health[grunt]-= state.playerDamage;
			world.registry.DestroyEntity(bullet);
		}
	}
}