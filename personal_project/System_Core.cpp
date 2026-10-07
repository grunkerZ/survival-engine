#include "System.h"
#include <iostream>
#include <cstdlib>
#include "MathUtils.h"
#include <cmath>
#include "EntityFactory.h"

void Quit(EngineContext& engine) {
	engine.assets.Clear();
	SDL_DestroyRenderer(engine.renderer);
	SDL_DestroyWindow(engine.window);
	IMG_Quit();
	TTF_CloseFont(engine.debugFont);
	TTF_Quit();
	SDL_Quit();
}

int Init(EngineContext& engine, Uint32 flags) {
	if (SDL_Init(flags) < 0) {
		std::cout << "\n*** CRITICAL ERROR: SDL failed init: " << SDL_GetError() << " ***\n" << std::endl;
		Quit(engine);
		return -1;
	}

	engine.window = SDL_CreateWindow("simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, 0);
	engine.renderer = SDL_CreateRenderer(engine.window, -1, SDL_RENDERER_ACCELERATED);

	if (!engine.window || !engine.renderer) {
		std::cout << "\n*** CRITICAL ERROR: SDL window/render failed: " << SDL_GetError() << " ***\n" << std::endl;
		Quit(engine);
		return -1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cout << "\n*** CRITICAL ERROR: SDL_IMAGE failed init: " << IMG_GetError() << " ***\n" << std::endl;
		Quit(engine);
		return -1;
	}

	if (TTF_Init() != 0) {
		std::cout << "\n*** CRITICAL ERROR: SDL_IMAGE failed init: " << TTF_GetError() << " ***\n" << std::endl;
		Quit(engine);
		return -1;
	}

	engine.debugFont = TTF_OpenFont("debug.ttf", 24);

	return 0;
}

void ProcessEvent(EngineContext& engine) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			engine.running = 0;
		}
	}
}

void LifeCycleSystem(WorldData& world) {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (world.registry.isActive[i]) {
			float left = world.camera.x - 250.0f;
			float right = world.camera.x + SCREEN_W + 250.0f;
			float top = world.camera.y - 250.0f;
			float bottom = world.camera.y + SCREEN_H + 250.0f;
			if (world.registry.position[i].x < left || world.registry.position[i].x > right || world.registry.position[i].y < top || world.registry.position[i].y > bottom) {
				if (world.registry.isProjectile[i]) {
					world.registry.DestroyEntity(i);
					std::cout << "Entity Destroyed: Off Screen" << std::endl;
				}
				else if (world.registry.hasAIController[i]) {
					Vector2D pos = GetRandomOffscreenPosition(world.camera);
					world.registry.position[i].x = pos.x;
					world.registry.position[i].y = pos.y;

					std::cout << "Monster Respawned: Off Screen" << std::endl;
				}
			}
		}

		if (world.registry.health[i] <= 0 && world.registry.hasAIController[i]) {
			SpawnXP(world.registry, world.registry.position[i].x, world.registry.position[i].y);
			world.registry.DestroyEntity(i);
		}
	}
}

