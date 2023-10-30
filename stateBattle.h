
#include "monster.h"
#include "player.h"

#ifndef STATEBATTLE
#define STATEBATTLE

// #include <string>

class StateBattle {

// private:
//     Player *p_player; 
//     Monster *p_monster;

public:

    // StateBattle(Player& player, Monster& monster);

    void loadInterface(Player& player, Monster& monster);
    void printSprite(Monster& monster);
    std::string getRandomLine();
    bool readySetFight(Player& player, Monster& monster);
};

#endif //STATEBATTLE