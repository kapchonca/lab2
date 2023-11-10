#ifndef GAMEMANAGER
#define GAMEMANAGER
 
#include "../h/map.h"
#include "../h/stateBattle.h"
#include "../h/chest.h"

class GameManager {

protected:

    int loopCounter = 0;
    
    bool s_GameIsOver = false;

    Player* player;

    StateBattle battle;


public:

    GameManager();

    ~GameManager() {delete player;};


    void StateHandler();

    std::string getRandomLine();

    void loadInterface(Player* player, Monster& monster);

    void printSprite(Monster monster);

    bool gameIsOver();

    void setGameOver();

    void increaseLoopCount();

    void stateInventory(Player* player);

    void recieveLoot(Player* player, Monster& monster);

    Monster getRandomMonster(Player* player);

    void windowInitializer();

};

#endif //GAMEMANAGER