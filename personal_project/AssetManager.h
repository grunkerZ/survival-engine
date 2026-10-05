#pragma once
#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <map>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

struct AssetManager {
	std::map<std::string, SDL_Texture*> textures;

	void AddTexture(SDL_Renderer* renderer, std::string id, const char* filepath) {
		textures.insert({ id, IMG_LoadTexture(renderer, filepath) });
		if (textures[id] == nullptr) {
			std::cout << "ERROR: Texture failed to load: " << IMG_GetError() << std::endl;
		}
	}

	SDL_Texture* GetTexture(std::string id) {
		return textures[id];
	}

	void Clear() {
		for (auto& pair : textures) {
			SDL_DestroyTexture(pair.second);
		}
		textures.clear();
	}
};

#endif //__ASSET_MANAGER_H__