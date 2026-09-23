#include <iostream>
#include "Engine.h"
#include <cstdlib>

GameEngine game;

int main(int argc, char* argv[]) {
	int player = game.registry.CreateEntity();
	game.registry.position[player].x = 0;
	game.registry.position[player].y = 300;
	game.registry.bounds[player] = { (int)(game.registry.position[player].x), (int)(game.registry.position[player].y), 32, 32 };
	game.registry.hasPlayerController[player] = true;

	if (game.Init(SDL_INIT_VIDEO) < 0) {
		return -1;
	}

	Uint64 lastTime = SDL_GetTicks64();

	game.assets.AddTexture(game.renderer, "player", "sprites/fb5.png");
	game.assets.AddTexture(game.renderer, "skull", "sprites/fb225.png");
	game.assets.AddTexture(game.renderer, "projectile", "sprites/fa212.png");
	game.assets.AddTexture(game.renderer, "xp", "sprites/fb161.png");
	game.registry.sprites[player] = game.assets.GetTexture("player");

	game.running = 1;

	while (game.running) {
		Uint64 currentTime = SDL_GetTicks64();
		game.dt = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		game.camera.x = game.registry.position[player].x - (SCREEN_W/2.0f);
		game.camera.y = game.registry.position[player].y - (SCREEN_H/2.0f);

		game.ProcessEvent();

		game.EnemySpawnerSystem(game.dt);
		game.PlayerInputSystem(game.dt);
		game.AutoShootSystem();
		game.EnemyAISystem();
		game.PhysicsSystem(game.dt);
		game.UpdateSpatialGrid();
		game.CollisionSystem();
		game.LifeCycleSystem();

		game.ClearScreen(255, 0, 0, 255);
		game.RenderSystem();
		game.PresentScreen();

		Uint64 workingTime = SDL_GetTicks64() - currentTime;
		if (workingTime < 16.6f) {
			SDL_Delay(16.6f - workingTime);
		}

		//std::cout << "FPS: " << (1000.0f / (SDL_GetTicks64() - frameStart)) << std::endl;
		//std::cout << "Player Pos: (" << game.registry.position[player].x << ", " << game.registry.position[player].y << ")" << std::endl;

	}

	game.Quit();

	return 0;
}