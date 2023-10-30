#ifndef GAMEMANAGER
#define GAMEMANAGER

#include "player.h"
#include "monster.h"
#include "map.h"
#include "progen.h"
#include "stateBattle.h"
#include <string>


class GameManager {

protected:

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
};

#endif //GAMEMANAGER