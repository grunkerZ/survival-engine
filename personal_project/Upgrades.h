#pragma once
#ifndef __UPGRADES_H__
#define __UPGRADES_H__

#include <string>
#include <vector>

enum ItemID {
	ITEM_SLINGSHOT,
	ITEM_EXPANSION_SPELL,
	ITEM_MULTIPLIER,
	ITEM_MAX
};

enum ItemCategory {
	ITEM_WEAPON,
	ITEM_PASSIVE
};

struct ItemLevelData {
	std::string description;
	float cooldownMod = 0.0f;
	int damageMod = 0;
	float areaMod = 0.0f;
	int amountMod = 0;
};

struct Item {
	ItemID id;
	std::string name;
	ItemCategory category;
	int maxLevel;
	std::vector<ItemLevelData> levels;
};

void CreateItem(Item& item, ItemID id, std::string name, ItemCategory category, int maxLevel);

#endif //__UPGRADES_H__