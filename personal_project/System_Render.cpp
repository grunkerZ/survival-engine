#include "GameData.h"

void GameEngine::RenderSystem() {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (registry.isActive[i] && (registry.sprites[i] != nullptr)) {
			SDL_Rect renderArea = registry.bounds[i];
			renderArea.x = (int)(registry.position[i].x - camera.x);
			renderArea.y = (int)(registry.position[i].y - camera.y);
			SDL_RenderCopy(renderer, registry.sprites[i], NULL, &renderArea);
		}
	}
}

void GameEngine::ClearScreen(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void GameEngine::PresentScreen() {
	SDL_RenderPresent(renderer);
}

void GameEngine::RenderUI() {
	std::string uiText = "FPS: " + std::to_string(currentFps) + " | Entities: " + std::to_string(registry.activeEntityCount);

	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(debugFont, uiText.c_str(), white);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect uiBounds = { 10, 10, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &uiBounds);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}