#ifndef GAMEMANAGER
#define GAMEMANAGER

#include "player.h"
#include "monster.h"
#include "map.h"
#include "progen.h"
#include "stateBattle.h"
#include "chest.h"
#include "potions.h"
#include "inventory.h"
#include <string>


class GameManager {

protected:

    int loopCounter = 0;
    bool s_GameIsOver = false;

public:

    // bool StateBattle(Player& player, Monster& monster); 
    // void StateIdle(Player& player, Monster& monster);
    void StateHandler();
    std::string getRandomLine();
    void loadInterface(Player& player, Monster& monster);
    void printSprite(Monster monster);

    bool gameIsOver();

    void setGameOver();

    void increaseLoopCount();

    void stateInventory(Player& player);

    void recieveLoot(Player& player, Monster& monster);

    Monster getRandomMonster(Player& player);

};

#endif //GAMEMANAGER