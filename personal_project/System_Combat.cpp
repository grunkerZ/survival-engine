#include "System.h"
#include "MathUtils.h"
#include "EntityFactory.h"
#include <algorithm>

void PlayerAutoShootSystem(GameState& state, Registry& registry, float dt) {
	int id = -1;
	for (int i = 0; i < MAX_SLOTS; i++) {
		if (state.equippedWeapons[i].id == ITEM_SLINGSHOT) {
			id = i;
			break;
		}
	}
	if (id == -1) return;
	ActiveWeapon& weapon = state.equippedWeapons[id];

	weapon.fireTimer -= dt;
	if (weapon.fireTimer <= 0.0f) {
		float px = registry.position[state.playerID].x;
		float py = registry.position[state.playerID].y;

		std::vector<std::pair<float, int>> targets;

		for (int i = 0; i < MAX_ENTITIES; i++) {
			if (registry.isActive[i] && registry.hasAIController[i]) {
				float dist = GetDistance(px, py, registry.position[i].x, registry.position[i].y);
				if(dist <= 800) targets.push_back({ dist, i });
			}
		}

		std::sort(targets.begin(), targets.end());

		if(!targets.empty()){
			for (int i = 0; i < (weapon.baseAmt + state.playerAmount); i++) {
				int idx = i % targets.size();
				int targetId = targets[idx].second;
				int bullet = SpawnBullet(registry, px, py, weapon.baseDmg);
				if (bullet == -1) {
					return;
				}

				Vector2D dir = GetDirection(registry.position[targetId].x, registry.position[targetId].y, px, py);
				registry.velocity[bullet].dx = dir.x * 250.0f;
				registry.velocity[bullet].dy = dir.y * 250.0f;
				registry.bounds[bullet].w *= weapon.baseArea * state.playerArea;
				registry.bounds[bullet].h *= weapon.baseArea * state.playerArea;

				weapon.fireTimer = state.maxFireCooldown * weapon.baseCD * state.playerCooldownMod;
			}
		}
		targets.clear();
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