#include "../h/potions.h"

void PotionOfHealSmall::useItem(Player* player) {

    int effect = player->getHealthMax() / 4;
    player->increaseHealth(effect);
    
}

void PotionOfHealMedium::useItem(Player* player) {

    int effect = player->getHealthMax() / 2;
    player->increaseHealth(effect);
    
}

void AttackScroll::useItem(Player* player) {

    player->setAttackPoints(player->getAttackPoints() + 1);
        
}

void HealthScroll::useItem(Player* player) {

    player->setHealthMax(player->getHealthMax() + 20);
        
}


void Item::decreaseItemCounter(Player* player) {
    player->getInventory()->reduceItemCount(name);
}