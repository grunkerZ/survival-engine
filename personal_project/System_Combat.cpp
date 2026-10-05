#include "GameData.h"
#include "MathUtils.h"

void GameEngine::AutoShootSystem() {
	maxFireCooldown -= dt;
	if (maxFireCooldown <= 0.0f) {
		float px, py;
		for (int i = 0; i < MAX_ENTITIES; i++) {
			if (registry.isActive[i] && registry.hasPlayerController[i]) {
				px = registry.position[i].x;
				py = registry.position[i].y;
			}
		}

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
			int bullet = registry.CreateEntity();
			if (bullet == -1) {
				std::cout << "WARNING: Max Entity Limit Reached" << std::endl;
				return;
			}

			registry.position[bullet].x = px;
			registry.position[bullet].y = py;
			registry.bounds[bullet] = { (int)(registry.position[bullet].x), (int)(registry.position[bullet].y), 16, 16 };
			registry.sprites[bullet] = assets.GetTexture("projectile");
			registry.isProjectile[bullet] = true;

			Vector2D dir = GetDirection(registry.position[targetId].x, registry.position[targetId].y, px, py);
			registry.velocity[bullet].dx = dir.x * 250.0f;
			registry.velocity[bullet].dy = dir.y * 250.0f;

			maxFireCooldown = 1.0f;
		}
	}
}

void GameEngine::CollisionSystem() {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isActive[i] && registry.hasAIController[i]) {
			int row = (int)(registry.position[i].y / CELL_SIZE);
			int col = (int)(registry.position[i].x / CELL_SIZE);

			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					std::pair<int, int> checkPos = { col + x, row + y };
					for (int j : spatialGrid[checkPos]) {
						if (!registry.isActive[j]) continue;
						if (registry.hasAIController[j]) {
							if (i >= j) continue;
							if (SDL_HasIntersection(&registry.bounds[i], &registry.bounds[j])) {
								Vector2D dir = GetDirection(registry.position[j].x, registry.position[j].y, registry.position[i].x, registry.position[i].y);
								registry.position[j].x += dir.x * 1.5f;
								registry.position[j].y += dir.y * 1.5f;
								registry.position[i].x -= dir.x * 1.5f;
								registry.position[i].y -= dir.y * 1.5f;
							}
						}
						if (registry.isProjectile[j]) {
							if (SDL_HasIntersection(&registry.bounds[i], &registry.bounds[j])) {
								registry.health[i]--;
								registry.DestroyEntity(j);
								std::cout << "Monster Killed" << std::endl;
								break;
							}
						}
						if (registry.hasPlayerController[j]) {
							if (SDL_HasIntersection(&registry.bounds[i], &registry.bounds[j])) {
								Vector2D dir = GetDirection(registry.position[j].x, registry.position[j].y, registry.position[i].x, registry.position[i].y);
								registry.position[i].x -= dir.x * 2.0f;
								registry.position[i].y -= dir.y * 2.0f;
							}
						}
					}
				}
			}

		}
		if (registry.hasPlayerController[i]) {
			float px = registry.position[i].x;
			float py = registry.position[i].y;
			int row = (int)(registry.position[i].y / CELL_SIZE);
			int col = (int)(registry.position[i].x / CELL_SIZE);

			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					std::pair<int, int> checkPos = { col + x, row + y };
					for (int j : spatialGrid[checkPos]) {
						if (!registry.isActive[j]) continue;
						if (registry.isExperience[j]) {
							float dist = sqrt(GetDistanceSq(registry.position[j].x, registry.position[j].y, px, py));
							if (dist <= 100) {
								Vector2D dir = GetDirection(px, py, registry.position[j].x, registry.position[j].y);
								registry.velocity[j].dx = dir.x * 200;
								registry.velocity[j].dy = dir.y * 200;
							}
							if (SDL_HasIntersection(&registry.bounds[i], &registry.bounds[j])) {
								registry.DestroyEntity(j);
								playerXP++;
								if (playerXP >= xpToNextLvl) {
									playerLvl++;
									maxFireCooldown -= 0.01f;
									playerXP - xpToNextLvl;
									xpToNextLvl += 10;
								}
								std::cout << "XP GAINED" << std::endl;
							}
						}
					}
				}
			}
		}
	}
}