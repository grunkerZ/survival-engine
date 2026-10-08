#include "EntityFactory.h"

int SpawnGrunt(Registry& registry, float x, float y) {
	int monster = registry.CreateEntity();

	if (monster == -1) {
		std::cout << "WARNING: ENTITY LIMIT REACHED" << std::endl;
		return -1;
	}

	registry.position[monster].x = x;
	registry.position[monster].y = y;
	registry.bounds[monster] = { 0, 0, 32, 32 };
	registry.bounds[monster].y = registry.position[monster].y - (registry.bounds[monster].h / 2.0f);
	registry.bounds[monster].x = registry.position[monster].x - (registry.bounds[monster].w / 2.0f);
	registry.entityType[monster] = ET_GRUNT;
	registry.hasAIController[monster] = true;
	registry.health[monster] = 2;

	return monster;
}

int SpawnBullet(Registry& registry, float x, float y, int damage) {
	int bullet = registry.CreateEntity();

	if (bullet == -1) {
		std::cout << "WARNING: ENTITY LIMIT REACHED" << std::endl;
		return -1;
	}

	registry.position[bullet].x = x;
	registry.position[bullet].y = y;
	registry.bounds[bullet] = { 0, 0, 16, 16 };
	registry.bounds[bullet].y = registry.position[bullet].y - (registry.bounds[bullet].h / 2.0f);
	registry.bounds[bullet].x = registry.position[bullet].x - (registry.bounds[bullet].w / 2.0f);
	registry.entityType[bullet] = ET_BULLET;
	registry.isProjectile[bullet] = true;
	registry.damage[bullet] = damage;
	

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
	registry.bounds[xp] = { 0, 0, 16, 16 };
	registry.bounds[xp].y = registry.position[xp].y - (registry.bounds[xp].h / 2.0f);
	registry.bounds[xp].x = registry.position[xp].x - (registry.bounds[xp].w / 2.0f);
	registry.entityType[xp] = ET_XP;
	registry.isExperience[xp] = true;

	return xp;
}