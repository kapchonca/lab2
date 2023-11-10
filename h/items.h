#ifndef POTIONS
#define POTIONS

#include "../h/player.h"

class PotionOfHealSmall;
class PotionOfHealMedium;
class HealthScroll;
class AttackScroll;

class Item {

protected:
    int itemInd;

public:

    static Item* createItem(int itemType);

    void decreaseItemCounter(Player* player);

    virtual void useItem(Player* player) = 0;


};

class Potion: public Item {

public:

    virtual void useItem(Player* player) = 0;

    virtual void displayPotionInfo() = 0;
};

class Scroll: public Item {

public:

    virtual void useItem(Player* player) = 0;

    virtual void displayScrollInfo() = 0;

};


class PotionOfHealSmall: public Potion {

public:

    void useItem(Player* player) override;

    void displayPotionInfo() override;
    
};

class PotionOfHealMedium: public Potion {

public:

    void useItem(Player* player) override;

    void displayPotionInfo() override;

};

class AttackScroll: public Scroll {

public:

    void useItem(Player* player) override;

    void displayScrollInfo() override;

};

class HealthScroll: public Scroll {

public:

    void useItem(Player* player) override;

    void displayScrollInfo() override;

};



#endif //POTIONS