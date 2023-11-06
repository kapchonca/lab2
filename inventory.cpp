#include "inventory.h"
#include <ncurses.h>
#include <algorithm>

Inventory::Inventory() {
    loot["SmallHeal"] = 0;
    loot["MediumHeal"] = 0;
}


void Inventory::showInventory() {

    clear();

    for (int i = 1; i < 3; i++) {
        switch (i) {
            case 1:
                mvprintw(15 + i, 100, "Small potions of heal: %d", loot["SmallHeal"]);
                break;
            case 2:
                mvprintw(15 + i, 100, "Medium potions of heal: %d", loot["MediumHeal"]);
                break;
        }

    }

    refresh();

}

void Inventory::reduceItemCount(std::string item) {
    loot[item]--;
}

void Inventory::addItem(std::string item) {
    loot[item]++;
}

std::unordered_map<std::string, int> Inventory::getLoot() {
    return loot;
}