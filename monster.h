#include <string>
#include "player.h"

#ifndef MONSTER
#define MONSTER


class Monster {

private:
    int monsterTime;
    int healthMax;
    int healthPoints;
    int attackPoints;
    std::string name = "DRAGON";
    std::string spriteInd = "1";
    // int positionX = 2;
    // int positionY = 1;
    float baseModifier;

public:

    Monster(Player& player);

    int getTime();
    int getHealthMax();
    int getHealthPoints();
    int getAttackPoints();
    int getPositionX();
    int getPositionY();
    std::string getName();
    std::string getSpriteInd();

    void decreaseHealth(int attack);

    void setHealthPoints(int healthPoints);
};

#endif // MONSTER