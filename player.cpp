#include "player.h"

void Player::decreaseHealth(int attackPoints) {
    healthPoints -= attackPoints;
}

void Player::increaseHealth(int healPoints) {
    healthPoints += healPoints;
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

