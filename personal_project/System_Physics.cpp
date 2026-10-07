#include "System.h"
#include "MathUtils.h"

void PhysicsSystem(Registry& registry, float dt) {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isActive[i]) {
			registry.position[i].x += registry.velocity[i].dx * dt;
			registry.position[i].y += registry.velocity[i].dy * dt;
			registry.bounds[i].y = registry.position[i].y - (registry.bounds[i].h / 2.0f);
			registry.bounds[i].x = registry.position[i].x - (registry.bounds[i].w / 2.0f);
		}
	}
}

void PlayerInputSystem(Registry& registry) {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isActive[i] && registry.hasPlayerController[i]) {
			const Uint8* state = SDL_GetKeyboardState(NULL);

			float dx = 0;
			float dy = 0;
			registry.velocity[i].dy = 0;
			registry.velocity[i].dx = 0;

			if (state[SDL_SCANCODE_W]) {
				dy -= 1;
			}
			if (state[SDL_SCANCODE_A]) {
				dx -= 1;
			}
			if (state[SDL_SCANCODE_S]) {
				dy += 1;
			}
			if (state[SDL_SCANCODE_D]) {
				dx += 1;
			}

			if (dy || dx) {
				Normalize(dx, dy);
			}
			registry.velocity[i].dx += (dx * 100);
			registry.velocity[i].dy += (dy * 100);
		}
	}
}

void CollisionDetectionSystem(WorldData& world) {
	world.collisionEvents.clear();

	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (!world.registry.isActive[i]) continue;

		int row = (int)(world.registry.position[i].y / CELL_SIZE);
		int col = (int)(world.registry.position[i].x / CELL_SIZE);

		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				std::pair<int, int> checkPos = { col + x, row + y };
				for (int j : world.spatialGrid[checkPos]) {
					if (!world.registry.isActive[j]) continue;
					if (i >= j) continue;
					if (SDL_HasIntersection(&world.registry.bounds[i], &world.registry.bounds[j])) {
						world.collisionEvents.push_back({ i, j });
					}
				}
			}
		}
	}
}

void SeperationResolutionSystem(WorldData& world) {
	for (const auto& event : world.collisionEvents) {
		int player = -1;
		int grunt = -1;

		if (world.registry.hasAIController[event.entityA] && world.registry.hasAIController[event.entityB]) {
			if (!world.registry.isActive[event.entityA] || !world.registry.isActive[event.entityB]) continue;

			Vector2D dir = GetDirection(world.registry.position[event.entityA].x, world.registry.position[event.entityA].y, world.registry.position[event.entityB].x, world.registry.position[event.entityB].y);
			world.registry.position[event.entityA].x += (1.5f * dir.x);
			world.registry.position[event.entityB].x -= (1.5f * dir.x);
			world.registry.position[event.entityA].y += (1.5f * dir.y);
			world.registry.position[event.entityB].y -= (1.5f * dir.y);
		}
		else if (world.registry.hasPlayerController[event.entityA] && world.registry.hasAIController[event.entityB]) {
			player = event.entityA;
			grunt = event.entityB;
		}
		else if (world.registry.hasPlayerController[event.entityB] && world.registry.hasAIController[event.entityA]) {
			player = event.entityB;
			grunt = event.entityA;
		}

		if (player != -1 && grunt != -1) {
			if (!world.registry.isActive[player] || !world.registry.isActive[grunt]) continue;
			Vector2D dir = GetDirection(world.registry.position[player].x, world.registry.position[player].y, world.registry.position[grunt].x, world.registry.position[grunt].y);
			world.registry.position[player].x += (0.5f * dir.x);
			world.registry.position[grunt].x -= (2.0f * dir.x);
			world.registry.position[player].y += (0.5f * dir.y);
			world.registry.position[grunt].y -= (2.0f * dir.y);
		}
	}
}