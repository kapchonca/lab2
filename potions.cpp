#include "potions.h"

// void PotionOfHealSmall::drinkPotion(Player& player) {
//     int effect = player.getHealthMax() / 4;
//     player.increaseHealth(effect);
// }

void BasePotionOfHealing::drinkPotion(Player& player) {
    if (divider) {
        int effect = player.getHealthMax() / divider;
        player.increaseHealth(effect);
        if (player.getHealthPoints() > player.getHealthMax()) {
            player.setHealthPoints(player.getHealthMax());
        }
    }
}

PotionOfHealSmall::PotionOfHealSmall() {
    divider = 4;
}
PotionOfHealMedium::PotionOfHealMedium() {
    divider = 2;
}
// void PotionOfHealMedium::drinkPotion(Player& player) {
//     int effect = player.getHealthMax() / 2;
//     player.increaseHealth(effect);
// }