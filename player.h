#include <vector>
#include <string>
#ifndef PLAYER
#define PLAYER

#include "inventory.h"

class Player;

class Inventory {
private:

    // std::vector<int> loot; 

    std::unordered_map<std::string, int> loot;

public:

    void showInventory(Player& player);
    
    void addItem(std::string item);

    void reduceItemCount(std::string item);

    std::unordered_map<std::string, int> getLoot();

    Inventory();
};


class Player {

protected:

    int healthMax = 100;
    int healthPoints = 100;
    int attackPoints = 10;
    int level = 1;
    int xp = 0;
    int xpLimit = 50;

    Inventory playerInventory;
    // std::vector<int>* pInventory;
    // std::vector<std::string> consumables;
    // std::vector<std::string> equipment;

public:

    Player(Inventory inventory) : playerInventory(inventory) {}

    void levelUp();

    void addExp(int xp);

    // void addConsumable(std::string consumable);

    // void addEquipment(std::string equip);

    void decreaseHealth(int attackPoints);

    void increaseHealth(int healPoints);

    int getHealthPoints();

    int getHealthMax();

    int getAttackPoints();

    int getXpLimit();

    int getLevel();

    int getXp();

    Inventory* getInventory();

    void setHealthPoints(int healthPoints);
    // template <typename Stat>
    // Stat getValue(std::string value) {
    //     switch (value) {
    //         case "heal"
    //     }
    // }

    //smth else
};



#endif //PLAYER
