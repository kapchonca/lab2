#ifndef CHEST
#define CHEST

#include "potions.h"
#include <ncurses.h>
#include <fstream>

class Chest{

private:
    std::vector<int> loot;

public:
    Chest();

    std::vector<int> returnLoot();

    void displayChest();


};

#endif //CHEST

// chest indexes: 1 - medium heal, 2 - small heal