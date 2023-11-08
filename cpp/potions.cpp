#include "../h/potions.h"

void BasePotionOfHealing::drinkPotion(Player& player) {

    if (divider) {

        int effect = player.getHealthMax() / divider;
        player.increaseHealth(effect);
        
    }
}

PotionOfHealSmall::PotionOfHealSmall() {
    divider = 4;
}
PotionOfHealMedium::PotionOfHealMedium() {
    divider = 2;
}