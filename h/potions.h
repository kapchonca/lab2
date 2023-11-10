#ifndef POTIONS
#define POTIONS

#include "../h/player.h"


class Item {

public:
    std::string name = "";

public:

    void decreaseItemCounter(Player* player);

    virtual void useItem(Player* player) = 0;

};

class Potion: public Item {

public:

    virtual void useItem(Player* player) = 0;
};

class Scroll: public Item {

public:

    virtual void useItem(Player* player) = 0;

};


class PotionOfHealSmall: public Potion {

public:

    void useItem(Player* player) override;
    
};

class PotionOfHealMedium: public Potion {

public:

    void useItem(Player* player) override;

};

class AttackScroll: public Scroll {

public:

    void useItem(Player* player) override;

};

class HealthScroll: public Scroll {

public:

    void useItem(Player* player) override;

};



#endif //POTIONS