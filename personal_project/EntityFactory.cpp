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
	registry.bounds[monster].y = registry.position[monster].y - (registry.bounds[monster].h / 2.0f);
	registry.bounds[monster].x = registry.position[monster].x - (registry.bounds[monster].w / 2.0f);

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
	registry.bounds[bullet].y = registry.position[bullet].y - (registry.bounds[bullet].h / 2.0f);
	registry.bounds[bullet].x = registry.position[bullet].x - (registry.bounds[bullet].w / 2.0f);

	return bullet;
}

int SpawnXP(Registry& registry, float x, float y) {
	int xp = registry.CreateEntity();
	if (xp == -1) {
		std::cout << "WARNING: ENTITY LIMIT REACHED" << std::endl;
		return -1;
	}
	registry.position[xp].x = x;
	registry.position[xp].y = y;
	registry.bounds[xp] = { (int)(registry.position[xp].x - (registry.bounds[xp].w / 2.0f)), (int)(registry.position[xp].y - (registry.bounds[xp].h / 2.0f)), 16,16 };
	registry.entityType[xp] = ET_XP;
	registry.isExperience[xp] = true;

	return xp;
}