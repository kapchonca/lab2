#ifndef POTIONS
#define POTIONS

#include "player.h"

class BasePotionOfHealing {

protected:
    int divider;

public:
    void drinkPotion(Player& player);
};


class PotionOfHealSmall: public BasePotionOfHealing {
public:
    PotionOfHealSmall();

};

class PotionOfHealMedium: public BasePotionOfHealing {

public:
    PotionOfHealMedium();

};


#endif //POTIONS