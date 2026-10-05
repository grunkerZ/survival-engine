#include "GameData.h"

void GameEngine::PhysicsSystem(float dt) {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isActive[i]) {
			registry.position[i].x += registry.velocity[i].dx * dt;
			registry.position[i].y += registry.velocity[i].dy * dt;
			registry.bounds[i].y = registry.position[i].y;
			registry.bounds[i].x = registry.position[i].x;
		}
	}
}

void GameEngine::PlayerInputSystem(float dt) {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isActive[i] && registry.hasPlayerController[i]) {
			const Uint8* state = SDL_GetKeyboardState(NULL);

			registry.velocity[i].dy = 0;
			registry.velocity[i].dx = 0;

			if (state[SDL_SCANCODE_W]) {
				registry.velocity[i].dy -= 100;
			}
			if (state[SDL_SCANCODE_A]) {
				registry.velocity[i].dx -= 100;
			}
			if (state[SDL_SCANCODE_S]) {
				registry.velocity[i].dy += 100;
			}
			if (state[SDL_SCANCODE_D]) {
				registry.velocity[i].dx += 100;
			}
		}
	}
}