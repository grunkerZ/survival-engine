#include "System.h"

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

void RenderMap(WorldData& world, EngineContext& engine) {
	float cam_center_x = world.camera.x + (SCREEN_W / 2.0f);
	float cam_center_y = world.camera.y + (SCREEN_H / 2.0f);
	int chunk_cam_x = (int)floor(cam_center_x / (CHUNK_SIZE * CELL_SIZE));
	int chunk_cam_y = (int)floor(cam_center_y / (CHUNK_SIZE * CELL_SIZE));

	for (int y = -2; y <= 2; y++) {
		for (int x = -2; x <= 2; x++) {
			std::pair<int, int> checkPos = { chunk_cam_x + x, chunk_cam_y + y };
			const ChunkPrefab& prefab = world.availablePrefabs[world.loadedChunks[checkPos]];
			int chunkWorldX = checkPos.first * (CHUNK_SIZE * CELL_SIZE);
			int chunkWorldY = checkPos.second * (CHUNK_SIZE * CELL_SIZE);
			
			for (int tileY = 0; tileY < CHUNK_SIZE; tileY++) {
				for (int tileX = 0; tileX < CHUNK_SIZE; tileX++) {
					int tileOffsetX = tileX * CELL_SIZE;
					int tileOffsetY = tileY * CELL_SIZE;
					int worldX = chunkWorldX + tileOffsetX;
					int worldY = chunkWorldY + tileOffsetY;

					SDL_Rect dest = { worldX - (int)world.camera.x, worldY - (int)world.camera.y, CELL_SIZE, CELL_SIZE };

					int tileID = prefab.tiles[tileY][tileX];
					SDL_Rect tile = { 0, tileID * 32, 32, 32 };

					SDL_RenderCopy(engine.renderer, engine.textureMap[ET_TILESET], &tile, &dest);
				}
			}
		}
	}
}

void RenderSystem(WorldData& world, EngineContext& engine) {
	RenderMap(world, engine);

	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (world.registry.isActive[i]) {
			SDL_Texture* tex = engine.textureMap[world.registry.entityType[i]];
			if (tex != nullptr) {
				SDL_Rect renderArea = world.registry.bounds[i];
				renderArea.x -= world.camera.x;
				renderArea.y -= world.camera.y;
				SDL_RenderCopy(engine.renderer, tex, NULL, &renderArea);
			}
		}
	}
}