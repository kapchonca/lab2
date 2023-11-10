#include "../h/player.h"

Player::Player() {
    playerInventory = new Inventory;
}

void Player::decreaseHealth(int attackPoints) {
    healthPoints -= attackPoints;
}

void Player::increaseHealth(int healPoints) {
    healthPoints += healPoints;
    if (healthPoints > healthMax) {
        healthPoints = healthMax;
    }
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

int Player::getXpLimit() {
    return xpLimit;
}

int Player::getLevel() {
    return level;
}

int Player::getXp() {
    return xp;
}

Inventory* Player::getInventory() {
    return playerInventory;
}

void Player::setHealthPoints(int healthPoints) {
    this->healthPoints = healthPoints;
}

void Player::addExp(int xp) {
    this->xp += xp;
}

void Player::levelUp() {

    if (xp > xpLimit - 1) {

        xp-=xpLimit;
        xpLimit*=1.4;
        level+=1;

        healthMax*=1.2;
        attackPoints*=1.2;
    }

}

void Player::setHealthMax(int newHealth) {
    this->healthMax = newHealth;
}

void Player::setAttackPoints(int attackPoints) {
    this->attackPoints = attackPoints;
}


Inventory::Inventory() {

    loot["SmallHeal"] = 0;
    loot["MediumHeal"] = 0;
    loot["HealthIncrease"] = 0;
    loot["AttackIncrease"] = 0;

}

void Inventory::showInventory(Player* player) {

    clear();

    mvprintw(12, 100, "Health: %d/%d", player->getHealthPoints(), player->getHealthMax());
    mvprintw(13, 100, "Attack: %d", player->getAttackPoints());
    mvprintw(14, 100, "Level: %d", player->getLevel());
    mvprintw(15, 100, "Xp: %d/%d", player->getXp(), player->getXpLimit());

    for (int i = 1; i < 5; i++) {

        switch (i) {

            case 1:
                mvprintw(15 + i, 100, "Small potions of heal: %d", loot["SmallHeal"]);
                break;

            case 2:
                mvprintw(15 + i, 100, "Medium potions of heal: %d", loot["MediumHeal"]);
                break;

            case 3:
                mvprintw(15 + i, 100, "Health increase potions: %d", loot["HealthIncrease"]);
                break;

            case 4:
                mvprintw(15 + i, 100, "Attack increase potions: %d", loot["AttackIncrease"]);
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