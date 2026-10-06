#include "EntityFactory.h"

int SpawnGrunt(Registry& registry, float x, float y) {
	int monster = registry.CreateEntity();

	if (monster == -1) {
		std::cout << "WARNING: ENTITY LIMIT REACHED" << std::endl;
		return -1;
	}

	registry.position[monster].x = x;
	registry.position[monster].y = y;
	registry.bounds[monster] = { (int)(registry.position[monster].x), (int)(registry.position[monster].y), 32, 32 };
	registry.entityType[monster] = ET_GRUNT;
	registry.hasAIController[monster] = true;
	registry.health[monster] = 2;

	return monster;
}

int SpawnBullet(Registry& registry, float x, float y) {
	int bullet = registry.CreateEntity();

	if (bullet == -1) {
		std::cout << "WARNING: ENTITY LIMIT REACHED" << std::endl;
		return -1;
	}

	registry.position[bullet].x = x;
	registry.position[bullet].y = y;
	registry.bounds[bullet] = { (int)(registry.position[bullet].x), (int)(registry.position[bullet].y), 16, 16 };
	registry.entityType[bullet] = ET_BULLET;
	registry.isProjectile[bullet] = true;

	return bullet;
}