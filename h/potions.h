#ifndef POTIONS
#define POTIONS

#include "../h/player.h"

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