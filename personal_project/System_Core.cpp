#include "GameData.h"
#include <iostream>
#include <cstdlib>
#include "MathUtils.h"
#include <cmath>


int GameEngine::Init(Uint32 flags) {
	if (SDL_Init(flags) < 0) {
		std::cout << "\n*** CRITICAL ERROR: SDL failed init: " << SDL_GetError() << " ***\n" << std::endl;
		Quit();
		return -1;
	}

	window = SDL_CreateWindow("simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!window || !renderer) {
		std::cout << "\n*** CRITICAL ERROR: SDL window/render failed: " << SDL_GetError() << " ***\n" << std::endl;
		Quit();
		return -1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cout << "\n*** CRITICAL ERROR: SDL_IMAGE failed init: " << IMG_GetError() << " ***\n" << std::endl;
		Quit();
		return -1;
	}

	if (TTF_Init() != 0) {
		std::cout << "\n*** CRITICAL ERROR: SDL_IMAGE failed init: " << TTF_GetError() << " ***\n" << std::endl;
		Quit();
		return -1;
	}

	debugFont = TTF_OpenFont("debug.ttf", 24);

	return 0;
}

void GameEngine::ProcessEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			GameEngine::running=0;
		}
		if (event.type == SDL_KEYDOWN) {
			float left = camera.x - 150.0f;
			float right = camera.x + SCREEN_W + 150.0f;
			float top = camera.y - 150.0f;
			float bottom = camera.y + SCREEN_H + 150.0f;
			if (event.key.keysym.scancode == SDL_SCANCODE_1) {
				int monster = registry.CreateEntity();
				float edge = rand() % 4;

				if (edge == 0) {
					registry.position[monster].x = left;
					registry.position[monster].y = camera.y + rand() % SCREEN_H;
				}
				else if (edge == 1) {
					registry.position[monster].x = right;
					registry.position[monster].y = camera.y + rand() % SCREEN_H;
				}
				else if (edge == 2) {
					registry.position[monster].x = camera.x + rand() % SCREEN_W;
					registry.position[monster].y = top;
				}
				else if (edge == 3) {
					registry.position[monster].x = camera.x + rand() % SCREEN_W;
					registry.position[monster].y = bottom;
				}

				registry.bounds[monster] = { (int)(registry.position[monster].x), (int)(registry.position[monster].y), 32, 32 };
				registry.sprites[monster] = assets.GetTexture("skull");
				registry.hasAIController[monster] = true;
				registry.health[monster] = 2;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_2) {
				for (int i = 0; i < 10; i++) {
					int monster = registry.CreateEntity();
					float edge = rand() % 4;

					if (edge == 0) {
						registry.position[monster].x = left;
						registry.position[monster].y = camera.y + rand() % SCREEN_H;
					}
					else if (edge == 1) {
						registry.position[monster].x = right;
						registry.position[monster].y = camera.y + rand() % SCREEN_H;
					}
					else if (edge == 2) {
						registry.position[monster].x = camera.x + rand() % SCREEN_W;
						registry.position[monster].y = top;
					}
					else if (edge == 3) {
						registry.position[monster].x = camera.x + rand() % SCREEN_W;
						registry.position[monster].y = bottom;
					}

					registry.bounds[monster] = { (int)(registry.position[monster].x), (int)(registry.position[monster].y), 32, 32 };
					registry.sprites[monster] = assets.GetTexture("skull");
					registry.hasAIController[monster] = true;
					registry.health[monster] = 2;
				}
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_3) {
				for (int i = 0; i < 50; i++) {
					int monster = registry.CreateEntity();
					float edge = rand() % 4;

					if (edge == 0) {
						registry.position[monster].x = left;
						registry.position[monster].y = camera.y + rand() % SCREEN_H;
					}
					else if (edge == 1) {
						registry.position[monster].x = right;
						registry.position[monster].y = camera.y + rand() % SCREEN_H;
					}
					else if (edge == 2) {
						registry.position[monster].x = camera.x + rand() % SCREEN_W;
						registry.position[monster].y = top;
					}
					else if (edge == 3) {
						registry.position[monster].x = camera.x + rand() % SCREEN_W;
						registry.position[monster].y = bottom;
					}

					registry.bounds[monster] = { (int)(registry.position[monster].x), (int)(registry.position[monster].y), 32, 32 };
					registry.sprites[monster] = assets.GetTexture("skull");
					registry.hasAIController[monster] = true;
					registry.health[monster] = 2;
				}
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				float px, py;
				for (int i = 0; i < MAX_ENTITIES; i++) {
					if (registry.isActive[i] && registry.hasPlayerController[i]) {
						px = registry.position[i].x;
						py = registry.position[i].y;
					}
				}
				for (int i = 0; i < 36; i++) {
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

					float angle = (i * (360.0f / 36.0f)) * (3.14159f / 180.0f);
					float dirX = std::cos(angle);
					float dirY = std::sin(angle);

					registry.velocity[bullet].dx = dirX * 250.0f;
					registry.velocity[bullet].dy = dirY * 250.0f;
				}
			}
		}
	}
}

void GameEngine::Quit() {
	assets.Clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_CloseFont(debugFont);
	TTF_Quit();
	SDL_Quit();
}

void GameEngine::LifeCycleSystem() {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isActive[i]) {
			float left = camera.x - 1000.0f;
			float right = camera.x + SCREEN_W + 1000.0f;
			float top = camera.y - 1000.0f;
			float bottom = camera.y + SCREEN_H + 1000.0f;
			if (registry.position[i].x < left || registry.position[i].x > right || registry.position[i].y < top || registry.position[i].y > bottom) {
				if (registry.isProjectile[i]) {
					registry.DestroyEntity(i);
					std::cout << "Entity Destroyed: Off Screen" << std::endl;
				}
				else if (registry.hasAIController[i]) {
					float left = camera.x - 150.0f;
					float right = camera.x + SCREEN_W + 150.0f;
					float top = camera.y - 150.0f;
					float bottom = camera.y + SCREEN_H + 150.0f;

					float edge = rand() % 4;

					if (edge == 0) {
						registry.position[i].x = left;
						registry.position[i].y = camera.y + rand() % SCREEN_H;
					}
					else if (edge == 1) {
						registry.position[i].x = right;
						registry.position[i].y = camera.y + rand() % SCREEN_H;
					}
					else if (edge == 2) {
						registry.position[i].x = camera.x + rand() % SCREEN_W;
						registry.position[i].y = top;
					}
					else if (edge == 3) {
						registry.position[i].x = camera.x + rand() % SCREEN_W;
						registry.position[i].y = bottom;
					}

					registry.bounds[i] = { (int)(registry.position[i].x), (int)(registry.position[i].y), 32, 32 };

					std::cout << "Monster Respawned: Off Screen" << std::endl;
				}
			}
		}

		if (registry.health[i] <= 0 && registry.hasAIController[i]) {
			int xp = registry.CreateEntity();
			registry.position[xp] = registry.position[i];
			registry.bounds[xp] = { (int)(registry.position[xp].x), (int)(registry.position[xp].y), 16,16 };
			registry.sprites[xp] = assets.textures["xp"];
			registry.isExperience[xp] = true;
			registry.DestroyEntity(i);
		}
	}
}

void GameEngine::UpdateSpatialGrid() {
	spatialGrid.clear();

	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isActive[i]){
			spatialGrid[{(int)(registry.position[i].x / CELL_SIZE), (int)(registry.position[i].y / CELL_SIZE)}].push_back(i);
		}
	}
}