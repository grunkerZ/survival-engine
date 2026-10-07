#include "System.h"
#include <fstream>
#include <string>

std::ifstream inFile;

void InitMapPrefabs(WorldData& world) {
	LoadMapPrefab(world, "prefabs/default.txt");
	LoadMapPrefab(world, "prefabs/x_path.txt");
	LoadMapPrefab(world, "prefabs/y_path.txt");
	LoadMapPrefab(world, "prefabs/plus_path.txt");
}

void LoadMapPrefab(WorldData& world, std::string filepath) {
	ChunkPrefab prefab;
	inFile.open(filepath);
	if (!inFile) {
		std::cout << "Warning: Could not open filepath: " << filepath << std::endl;
		return;
	}

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			inFile >> prefab.tiles[x][y];
		}
	}

	world.availablePrefabs.push_back(prefab);
	inFile.close();
}
