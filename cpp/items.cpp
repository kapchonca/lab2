#include "../h/items.h"

/* Good, Factory method! */
Item* Item::createItem(int itemType) {

    switch (itemType) {
        case 1:
            return new PotionOfHealSmall();
        case 2:
            return new PotionOfHealMedium();
        case 3:
            return new HealthScroll();
        default:
            return new AttackScroll();
    }

}


void PotionOfHealSmall::useItem(Player* player) {

    int effect = player->getHealthMax() / 4;
    player->increaseHealth(effect);
    
}

void PotionOfHealSmall::displayPotionInfo() {
    mvprintw(50, 100, "Restores 25%% of your full hp");
}

void PotionOfHealMedium::useItem(Player* player) {

    int effect = player->getHealthMax() / 2;
    player->increaseHealth(effect);
    
}

void PotionOfHealMedium::displayPotionInfo() {
    mvprintw(50, 100, "Restores 50%% of your full hp");
}

void AttackScroll::useItem(Player* player) {
    /* Тут возникает довольно сложная дискусcионная тема насчет того,
     * должны ли быть все поля класса с публичными сеттерами (что 
     * вообще-то все равно что оставить поля публичными и соответственно
     * нарушить инкапсуляцию), или это функции, которым требуется знать
     * о состоянии класса, должны определяться как friend. Лично я считаю,
     * что friend лучше, так как он только расширяет границу инкапсуляции,
     * а не полностью ее убирает */
    player->setAttackPoints(player->getAttackPoints() + 1);
        
}

void AttackScroll::displayScrollInfo() {
    mvprintw(50, 100, "Increases your attack by 1");
}

void HealthScroll::useItem(Player* player) {

    player->setHealthMax(player->getHealthMax() + 20);
        
}

void HealthScroll::displayScrollInfo() {
    mvprintw(50, 100, "Increases your health by 20");
}

void Item::decreaseItemCounter(Player* player) {
    player->getInventory()->reduceItemCount(itemInd);
}