#include "System.h"
#include <fstream>
#include <string>
#include <cmath>

void InitMapPrefabs(WorldData& world) {
	LoadMapPrefab(world, "prefabs/default.txt");
	LoadMapPrefab(world, "prefabs/x_path.txt");
	LoadMapPrefab(world, "prefabs/y_path.txt");
	LoadMapPrefab(world, "prefabs/plus_path.txt");
}

void LoadMapPrefab(WorldData& world, std::string filepath) {
	ChunkPrefab prefab = {};
	std::ifstream inFile; 
	inFile.open(filepath);
	if (!inFile) {
		std::cout << "Warning: Could not open filepath: " << filepath << std::endl;
		return;
	}

	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			inFile >> prefab.tiles[y][x];
		}
	}

	world.availablePrefabs.push_back(prefab);
}

void UpdateSpatialGrid(WorldData& world) {
	world.spatialGrid.clear();

	for (int i = 0; i < MAX_ENTITIES; i++) {
		if (world.registry.isActive[i]) {
			world.spatialGrid[{(int)(world.registry.position[i].x / CELL_SIZE), (int)(world.registry.position[i].y / CELL_SIZE)}].push_back(i);
		}
	}
}

void UpdateMapSystem(WorldData& world) {
	float cam_center_x = world.camera.x + (SCREEN_W / 2.0f);
	float cam_center_y = world.camera.y + (SCREEN_H / 2.0f);
	int chunk_cam_x = (int)floor(cam_center_x / (CHUNK_SIZE * CELL_SIZE));
	int chunk_cam_y = (int)floor(cam_center_y / (CHUNK_SIZE * CELL_SIZE));

	for (int y = -2; y <= 2; y++) {
		for (int x = -2; x <= 2; x++) {
			std::pair<int, int> checkPos = { chunk_cam_x + x, chunk_cam_y + y };
			if (world.loadedChunks.count(checkPos) == 0) {
				int r = 0;
				int chunkX = checkPos.first;
				int chunkY = checkPos.second;
				bool isHorizontalRoad = (chunkX % 3 == 0);
				bool isVerticalRoad = (chunkY % 3 == 0);

				if (isVerticalRoad && isHorizontalRoad) {
					r = 3;
				}
				else if (isVerticalRoad) {
					r = 1;
				}
				else if (isHorizontalRoad) {
					r = 2;
				}

				world.loadedChunks[checkPos] = r;
			}
		}
	}
}
