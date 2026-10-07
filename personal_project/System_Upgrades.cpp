#include "GameData.h"
#include <algorithm>
#include <random>

void CreateItem(Item& item, ItemID id, std::string name, ItemCategory category, int maxLevel) {
	item.id = id;
	item.name = name;
	item.category = category;
	item.maxLevel = maxLevel;
}

void InitUpgrades(WorldData& world) {
	CreateItem(world.items[ITEM_SLINGSHOT], ITEM_SLINGSHOT, "Slingshot", ITEM_WEAPON, 6);
	world.items[ITEM_SLINGSHOT].levels.push_back({ "Shoots a projectile at the nearest enemy.", 1.0f, 1, 1.0f, 1 });
	world.items[ITEM_SLINGSHOT].levels.push_back({ "Fires faster.", 0.8f, 1, 1.0f, 1 });
	world.items[ITEM_SLINGSHOT].levels.push_back({ "Deals More Damage.", 0.8f, 2, 1.0f, 1 });
	world.items[ITEM_SLINGSHOT].levels.push_back({ "Fires faster.", 0.6f, 2, 1.0f, 1 });
	world.items[ITEM_SLINGSHOT].levels.push_back({ "More Projectiles.", 1.0f, 2, 1.0f, 2 });
	world.items[ITEM_SLINGSHOT].levels.push_back({ "Fires Faster.", 0.4f, 2, 1.0f, 2 });

	CreateItem(world.items[ITEM_EXPANSION_SPELL], ITEM_EXPANSION_SPELL, "Expansion Spell", ITEM_PASSIVE, 6);
	world.items[ITEM_EXPANSION_SPELL].levels.push_back({ "Increases Area", 0.0f, 0, 1.1f, 0 });
	world.items[ITEM_EXPANSION_SPELL].levels.push_back({ "More Area.", 0.0f, 0, 1.2f, 0 });
	world.items[ITEM_EXPANSION_SPELL].levels.push_back({ "More Area.", 0.0f, 0, 1.3f, 0 });
	world.items[ITEM_EXPANSION_SPELL].levels.push_back({ "More Area.", 0.0f, 0, 1.3f, 0 });
	world.items[ITEM_EXPANSION_SPELL].levels.push_back({ "More Area.", 0.0f, 0, 1.4f, 0 });
	world.items[ITEM_EXPANSION_SPELL].levels.push_back({ "More Area.", 0.0f, 0, 1.5f, 0 });

	CreateItem(world.items[ITEM_MULTIPLIER], ITEM_MULTIPLIER, "Multiplier", ITEM_PASSIVE, 3);
	world.items[ITEM_MULTIPLIER].levels.push_back({ "Fire Additional Projectiles.", 0, 0, 0, 1 });
	world.items[ITEM_MULTIPLIER].levels.push_back({ "More Projectiles.", 0, 0, 0, 2 });
	world.items[ITEM_MULTIPLIER].levels.push_back({ "More Projectiles.", 0, 0, 0, 3 });
}

std::vector<ItemID> RollUpgrades(GameState& state, WorldData& world) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<ItemID> upgradePool;
	std::vector<ItemID> choices;

	for (int i = 0; i < ITEM_MAX; i++) {
		if (state.inventoryLevels[i] >= world.items[i].maxLevel) continue;
		if (state.inventoryLevels[i] == 0) {
			if (world.items[i].category == ITEM_WEAPON && state.currentWeaponCount >= state.MAX_SLOTS) continue;
			if (world.items[i].category == ITEM_PASSIVE && state.currentPassiveCount >= state.MAX_SLOTS) continue;
		}
		upgradePool.push_back(world.items[i].id);
	}
	std::shuffle(upgradePool.begin(), upgradePool.end(), gen);

	for (int i = 0; i < upgradePool.size(); i++) {
		choices.push_back(upgradePool[i]);
		if (choices.size() >= 3) break;
	}

	return choices;
}