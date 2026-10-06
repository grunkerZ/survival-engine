#include "System.h"

void RenderSystem(WorldData& world, EngineContext& engine) {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (world.registry.isActive[i]) {
			SDL_Texture* tex = engine.textureMap[world.registry.entityType[i]];
			if(tex != nullptr){
				SDL_Rect renderArea = world.registry.bounds[i];
				renderArea.x -= world.camera.x;
				renderArea.y -= world.camera.y;
				SDL_RenderCopy(engine.renderer, tex, NULL, &renderArea);
			}
		}
	}
}

void ClearScreen(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}

void PresentScreen(SDL_Renderer* renderer) {
	SDL_RenderPresent(renderer);
}

void RenderUI(EngineContext& engine, Registry& registry) {
	std::string uiText = "FPS: " + std::to_string(engine.currentFps) + " | Entities: " + std::to_string(registry.activeEntityCount);

	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(engine.debugFont, uiText.c_str(), white);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(engine.renderer, surface);

	SDL_Rect uiBounds = { 10, 10, surface->w, surface->h };
	SDL_RenderCopy(engine.renderer, texture, NULL, &uiBounds);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}