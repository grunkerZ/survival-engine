#include "System.h"
#include "MathUtils.h"
#include "EntityFactory.h"

void EnemyAISystem(Registry& registry) {
	float px, py;

	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isActive[i] && registry.hasPlayerController[i]) {
			px = registry.position[i].x;
			py = registry.position[i].y;
		}
	}

	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isActive[i] && registry.hasAIController[i]) {
			Vector2D dir = GetDirection(px, py, registry.position[i].x, registry.position[i].y);
			registry.velocity[i].dx = dir.x * 50.0f;
			registry.velocity[i].dy = dir.y * 50.0f;
		}
	}
}

void EnemySpawnerSystem(WorldData& world, GameState& state, float dt) {
	state.waveCooldown -= dt;
	state.enemyAmount = 5 + (state.difficulty * log(state.difficulty));
	if (state.waveCooldown <= 0.0f) {
		for (int i = 0; i < (int)(state.enemyAmount); i++) {
			Vector2D position = GetRandomOffscreenPosition(world.camera);
			SpawnGrunt(world.registry, position.x, position.y);
			std::cout << "Monster Spawned" << std::endl;
		}

		state.difficulty += 0.1;
		state.waveCooldown = 10.0f;
	}
}