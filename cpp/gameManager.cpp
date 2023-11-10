
#include "../h/gameManager.h"


GameManager::GameManager() {
    int loopCounter = 0;

    player = new Player();

}


bool GameManager::gameIsOver() {

    if (s_GameIsOver) {

        return true;

    } else {

        return false;

    }
}

void GameManager::setGameOver() {
    s_GameIsOver = true;
}

Monster GameManager::getRandomMonster(Player* player) {

    Monster monster(player);

    if (rand() % 3 == 0) {

        monster = Skeleton(player);

    } else if (rand() % 3 == 1) {

        monster = Vampire(player);

    } else {

        monster = Dragon(player);
    }
    return monster;
}

void GameManager::stateInventory(Player* player) {

    int ch;

    Inventory* inv = player->getInventory();

    while (true) {

        inv->showInventory(player);
        ch = getch();

        if (ch == 'f') {
            break;
        }

        if (ch == '1' and inv->getLoot()["SmallHeal"] != 0) {

            PotionOfHealSmall potion;
            inv->reduceItemCount("SmallHeal");
            potion.useItem(player);

        } else if (ch == '2' and inv->getLoot()["MediumHeal"] != 0) {

            PotionOfHealMedium potion;
            inv->reduceItemCount("MediumHeal");
            potion.useItem(player);
            
        } else if (ch == '3' and inv->getLoot()["HealthIncrease"] != 0) {

            HealthScroll potion;
            inv->reduceItemCount("HealthIncrease");
            potion.useItem(player);
            
        } else if (ch == '4' and inv->getLoot()["AttackIncrease"] != 0) {

            AttackScroll potion;
            inv->reduceItemCount("AttackIncrease");
            potion.useItem(player);
            
        }
        
        
    }

}

void GameManager::windowInitializer() {

    initscr(); // инициализирует библиотеку ncurses и подготавливает терминал к работе
    start_color(); // подключает поддержку цветов
    curs_set(0); // Hide the cursor

}

void GameManager::StateHandler() {

    windowInitializer();

    Map map(238, 59, 10);

    while (!gameIsOver()) {

        int interactionNum = map.movePlayer();

        if (interactionNum == 0) {

                setGameOver();

        } else if (interactionNum == 2) {

                clear();
                Chest chest;    
                
                if (chest.returnLoot()[0] == 1) {
                    
                    (player->getInventory())->addItem("SmallHeal");

                } else if (chest.returnLoot()[0] == 2) {
                    
                    player->getInventory()->addItem("MediumHeal");
                    
                } else if (chest.returnLoot()[0] == 3) {
                    
                    player->getInventory()->addItem("HealthIncrease");
                    
                } else if (chest.returnLoot()[0] == 4) {
                    
                    player->getInventory()->addItem("AttackIncrease");
                    
                }


                
                chest.displayChest();
                getch();

        } else if (interactionNum == 1) {

                Monster monster = getRandomMonster(player);

                if(battle.readySetFight(player, monster)) {

                    recieveLoot(player, monster);
                    clear();

                } else {

                    setGameOver();

                }

        } else if (interactionNum == 3) {

            stateInventory(player);

        } else if (interactionNum == 4) {

                Boss boss(player, loopCounter);

                if (battle.readySetFight(player, boss)) {

                    recieveLoot(player, boss);
                    map = Map(238, 59, 10);
                    increaseLoopCount();

                    clear();

                } else {

                    setGameOver();

                }

        }
    }

    endwin(); // закрытие окошка
}

void GameManager::recieveLoot(Player* player, Monster& monster) {

    int xpToGet = player->getXpLimit() / 10 + rand() % player->getXpLimit() / 10;

    player->addExp(xpToGet);
    player->levelUp();

    bool specialLoot = (rand() % 4) == 0;

    if (specialLoot && monster.getSpriteInd() == "1") {

        player->getInventory()->addItem("SmallHeal"); // дописать для остальных монстров

    }
}

void GameManager::increaseLoopCount() {

    loopCounter+=1;

}