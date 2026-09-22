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
	game.registry.sprites[player] = game.assets.GetTexture("player");

	for (int i = 0; i < 500; i++) {
		int monster = game.registry.CreateEntity();

		game.registry.position[monster].x = rand() % 800;
		game.registry.position[monster].y = rand() % 600;
		game.registry.bounds[monster] = { (int)(game.registry.position[monster].x), (int)(game.registry.position[monster].y), 32, 32 };
		game.registry.sprites[monster] = game.assets.GetTexture("skull");
	}

	game.running = 1;

	while (game.running) {
		Uint64 currentTime = SDL_GetTicks64();
		game.dt = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		game.ProcessEvent();

		game.PlayerInputSystem(game.dt);
		game.Update(game.dt);

		game.ClearScreen(255, 0, 0, 255);
		game.RenderSystem();
		game.PresentScreen();

		Uint64 workingTime = SDL_GetTicks64() - currentTime;
		if (workingTime < 16.6f) {
			SDL_Delay(16.6f - workingTime);
		}

		//std::cout << "FPS: " << (1000.0f / (SDL_GetTicks64() - frameStart)) << std::endl;
		std::cout << "Player Pos: (" << game.registry.position[player].x << ", " << game.registry.position[player].y << ")" << std::endl;

	}

	game.Quit();

	return 0;
}