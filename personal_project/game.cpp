#include <SDL.h>
#include <iostream>

struct GameEngine {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	float dt;
	bool running = 0;

	int Init(Uint32 flags) {
		if (SDL_Init(flags) < 0) {
			std::cout << "\n*** CRITICAL ERROR: SDL failed init: " << SDL_GetError() << " ***\n" << std::endl;
			Quit();
			return -1;
		}

		window = SDL_CreateWindow("simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (!window || !renderer) {
			std::cout << "\n*** CRITICAL ERROR: SDL window/render failed: " << SDL_GetError() << " ***\n" << std::endl;
			Quit();
			return -1;
		}

		return 0;
	}

	int ProcessEvent(SDL_EventType e) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == e) {
				return 1;
			}
		}
		return 0;
	}

	void RenderFrame(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	void Quit() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
};

GameEngine game;


int main(int argc, char* argv[]) {
	game.dt = SDL_GetTicks64();

	if (game.Init(SDL_INIT_VIDEO) < 0) {
		return -1;
	}

	game.running = 1;

	while (game.running) {
		Uint64 frameStart = SDL_GetTicks64();

		if (game.ProcessEvent(SDL_QUIT)) {
			return 0;
		}

		game.RenderFrame(255, 0, 0, 255);

		game.dt = SDL_GetTicks64() - frameStart;

		if (game.dt < 16.6f) {
			SDL_Delay(16.6f - game.dt);
		}

		//std::cout << "FPS: " << (1000.0f / (SDL_GetTicks64() - frameStart)) << std::endl;

	}

	return 0;
}