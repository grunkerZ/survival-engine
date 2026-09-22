#include <iostream>
#include "Engine.h"

GameEngine game;

int main(int argc, char* argv[]) {
	int player = game.registry.CreateEntity();
	game.registry.position[player].x = 0;
	game.registry.position[player].y = 300;
	game.registry.bounds[player] = { (int)(game.registry.position[player].x), (int)(game.registry.position[player].y), 32, 32 };

	if (game.Init(SDL_INIT_VIDEO) < 0) {
		return -1;
	}

	Uint64 lastTime = SDL_GetTicks64();

	game.registry.sprites[player] = IMG_LoadTexture(game.renderer, "sprites/fb5.png");
	if (game.registry.sprites[player] == nullptr) {
		std::cout << "ERROR: Texture failed to load: " << IMG_GetError() << std::endl;
	}

	game.running = 1;

	while (game.running) {
		Uint64 currentTime = SDL_GetTicks64();
		game.dt = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		game.ProcessEvent();

		game.Update(game.dt);

		game.ClearScreen(255, 0, 0, 255);
		SDL_RenderCopy(game.renderer, game.registry.sprites[player], NULL, &game.registry.bounds[player]);
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