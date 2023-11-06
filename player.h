#include <vector>
#include <string>
#ifndef PLAYER
#define PLAYER

class Player {

protected:

    int healthMax = 100;
    int healthPoints = 100;
    int attackPoints = 10;
    int level = 1;
    int xp = 0;
    int xpLimit = 100;

    // std::vector<int>* pInventory;
    // std::vector<std::string> consumables;
    // std::vector<std::string> equipment;

public:

    // void levelUp(int xp, int xpLimit);
    // void addConsumable(std::string consumable);

    // void addEquipment(std::string equip);

    void decreaseHealth(int attackPoints);

    void increaseHealth(int healPoints);

    int getHealthPoints();

    int getHealthMax();

    int getAttackPoints();

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
