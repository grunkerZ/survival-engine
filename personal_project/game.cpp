#include <iostream>
#include "System.h"
#include "EntityFactory.h"
#include <cstdlib>
#include <time.h>

EngineContext engine;
GameState state;
WorldData world;

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int player = world.registry.CreateEntity();
	world.registry.position[player].x = 0;
	world.registry.position[player].y = 300;
	world.registry.bounds[player] = { (int)(world.registry.position[player].x), (int)(world.registry.position[player].y), 32, 32 };
	world.registry.hasPlayerController[player] = true;
	world.registry.entityType[player] = ET_PLAYER;
	state.playerID = player;
	world.registry.bounds[player].y = world.registry.position[player].y - (world.registry.bounds[player].h / 2.0f);
	world.registry.bounds[player].x = world.registry.position[player].x - (world.registry.bounds[player].w / 2.0f);

	if (Init(engine, SDL_INIT_VIDEO) < 0) {
		return -1;
	}

	InitMapPrefabs(world);

	Uint64 lastTime = SDL_GetTicks64();

	engine.assets.AddTexture(engine.renderer, "player", "sprites/fb5.png");
	engine.assets.AddTexture(engine.renderer, "skull", "sprites/fb225.png");
	engine.assets.AddTexture(engine.renderer, "projectile", "sprites/fa212.png");
	engine.assets.AddTexture(engine.renderer, "xp", "sprites/fb161.png");
	engine.assets.AddTexture(engine.renderer, "tileset", "tileset.png");
	engine.textureMap[ET_PLAYER] = engine.assets.GetTexture("player");
	engine.textureMap[ET_GRUNT] = engine.assets.GetTexture("skull");
	engine.textureMap[ET_BULLET] = engine.assets.GetTexture("projectile");
	engine.textureMap[ET_XP] = engine.assets.GetTexture("xp");
	engine.textureMap[ET_TILESET] = engine.assets.GetTexture("tileset");

	engine.running = 1;
	state.difficulty = 1;

	while (engine.running) {
		Uint64 currentTime = SDL_GetTicks64();
		engine.dt = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;
		engine.fpsTimer += engine.dt;
		engine.frameCount++;
		if (engine.fpsTimer >= 1.0f) {
			engine.currentFps = engine.frameCount;
			engine.frameCount = 0;
			engine.fpsTimer = 0;
		}

		world.camera.x = world.registry.position[player].x - (SCREEN_W/2.0f);
		world.camera.y = world.registry.position[player].y - (SCREEN_H/2.0f);

		if (state.pendingUpgrades > 0) {
			state.paused = true;
		}
		else {
			state.paused = false;
			state.pendingUpgrades = 0;
		}

		ProcessEvent(engine, state);
		
		if(!state.paused) {
			PlayerInputSystem(world.registry);
			EnemyAISystem(world.registry);
			PlayerAutoShootSystem(state, world.registry, engine.dt);
			EnemySpawnerSystem(world, state, engine.dt);
			MagnetSystem(world.registry, state.playerID);

			PhysicsSystem(world.registry, engine.dt);

			UpdateMapSystem(world);
			UpdateSpatialGrid(world);
			CollisionDetectionSystem(world);

			CombatResolutionSystem(world);
			SeperationResolutionSystem(world);
			PickupResolutionSystem(world, state);

			LifeCycleSystem(world);
		}

		ClearScreen(engine.renderer, 30, 30, 30, 255);
		RenderSystem(world, engine);
		RenderUI(engine, world.registry, state, true);
		PresentScreen(engine.renderer);

		Uint64 workingTime = SDL_GetTicks64() - currentTime;
		if (workingTime < 16.6f) {
			SDL_Delay(16.6f - workingTime);
		}

		//std::cout << "FPS: " << (1000.0f / (SDL_GetTicks64() - frameStart)) << std::endl;
		//std::cout << "Player Pos: (" << game.registry.position[player].x << ", " << game.registry.position[player].y << ")" << std::endl;

	}

	Quit(engine);

	return 0;
}