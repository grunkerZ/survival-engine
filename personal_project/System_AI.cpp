#include "GameData.h"
#include "MathUtils.h"

void GameEngine::EnemyAISystem() {
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

void GameEngine::EnemySpawnerSystem(float dt) {
	waveCooldown -= dt;
	enemyAmount = 5 + (difficulty * log(difficulty));
	if (waveCooldown <= 0.0f) {
		float left = camera.x - 150.0f;
		float right = camera.x + SCREEN_W + 150.0f;
		float top = camera.y - 150.0f;
		float bottom = camera.y + SCREEN_H + 150.0f;

		for (int i = 0; i < 15; i++) {
			int monster = registry.CreateEntity();
			float edge = rand() % 4;

			if (edge == 0) {
				registry.position[monster].x = left;
				registry.position[monster].y = camera.y + rand() % SCREEN_H;
			}
			else if (edge == 1) {
				registry.position[monster].x = right;
				registry.position[monster].y = camera.y + rand() % SCREEN_H;
			}
			else if (edge == 2) {
				registry.position[monster].x = camera.x + rand() % SCREEN_W;
				registry.position[monster].y = top;
			}
			else if (edge == 3) {
				registry.position[monster].x = camera.x + rand() % SCREEN_W;
				registry.position[monster].y = bottom;
			}

			registry.bounds[monster] = { (int)(registry.position[monster].x), (int)(registry.position[monster].y), 32, 32 };
			registry.sprites[monster] = assets.GetTexture("skull");
			registry.hasAIController[monster] = true;
			registry.health[monster] = 2;

			std::cout << "Monster Spawned" << std::endl;
		}

		difficulty += 0.1;
		waveCooldown = 10.0f;
	}
}