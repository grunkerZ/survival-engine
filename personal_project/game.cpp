#include <iostream>
#include "Engine.h"

GameEngine game;

int main(int argc, char* argv[]) {
	game.dt = SDL_GetTicks64();

	int player = game.registry.CreateEntity();
	game.registry.position[player].x = 0;
	game.registry.position[player].y = 300;

	if (game.Init(SDL_INIT_VIDEO) < 0) {
		return -1;
	}

	game.running = 1;

	while (game.running) {
		Uint64 frameStart = SDL_GetTicks64();

		game.ProcessEvent();

		game.Update();

		game.RenderFrame(255, 0, 0, 255);

		game.dt = SDL_GetTicks64() - frameStart;

		if (game.dt < 16.6f) {
			SDL_Delay(16.6f - game.dt);
		}

		//std::cout << "FPS: " << (1000.0f / (SDL_GetTicks64() - frameStart)) << std::endl;
		std::cout << "Player Pos: (" << game.registry.position[player].x << ", " << game.registry.position[player].y << ")" << std::endl;

	}

	game.Quit();

	return 0;
}