#include "player.h"


// void Player::levelUp(int xp, int xpLimit) {
//     xpLimit *= 1.1;
//     xp = 0;
// }

// void Player::addConsumable(std::string consumable) {
//     consumables.push_back(consumable);
// }

// void Player::addEquipment(std::string equip) {
//     equipment.push_back(equip);
// }

void Player::decreaseHealth(int attackPoints) {
    healthPoints -= attackPoints;
}

int Player::getHealthPoints() {
    return healthPoints;
}

int Player::getHealthMax() {
    return healthMax;
}

int Player::getAttackPoints() {
    return attackPoints;
}

void Player::setHealthPoints(int healthPoints) {
    this->healthPoints = healthPoints;
}
// template <typename Stat>
// Stat getValue(std::string value) {
//     switch (value) {
//         case "heal"
//     }
// }

//smth else

