// #include <string>
#include "monster.h"
#include <ctime>
#include <algorithm>
#include <chrono>
#include <iostream>


Monster::Monster(Player& player) {
    srand(time(0));
    baseModifier = 1 + (rand() % 5) / 10.;
    healthMax = player.getAttackPoints() * 70 * baseModifier + rand() % 100;
    healthPoints = healthMax;
    attackPoints = player.getHealthMax() / 20 * baseModifier + rand() % 4;
    monsterTime = 40 * baseModifier;
}


int Monster::getTime() {
    return monsterTime;
}
int Monster::getHealthMax() {
    return healthMax;
}
int Monster::getHealthPoints() {
    return healthPoints;
}
int Monster::getAttackPoints() {
    return attackPoints;
}
// int Monster::getPositionX() {
//     return positionX;
// }
// int Monster::getPositionY() {
//     return positionY;
// }
std::string Monster::getName() {
    return name;
}
std::string Monster::getSpriteInd() {
    return spriteInd;
}
void Monster::decreaseHealth(int attack) {
    healthPoints-=attack;
}
void Monster::setHealthPoints(int healthPoints) {
    this->healthPoints = healthPoints;
}