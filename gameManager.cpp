#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "gameManager.h"

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

Monster GameManager::getRandomMonster(Player& player) {
    if (rand() % 3 == 0) {
        Skeleton monster(player);
        return monster;
    } else if (rand() % 3 == 1) {
        Vampire monster(player);
        return monster;
    } else {
        Dragon monster(player);
        return monster;
    }
}

void GameManager::stateInventory(Player& player) {
    int ch;
    Inventory* inv = player.getInventory();
    while (true) {
        inv->showInventory(player);
        ch = getch();

        if (ch == 'f') {
            break;
        }

        // BasePotionOfHealing potion;
        if (ch == '1' and inv->getLoot()["SmallHeal"] != 0) {
            PotionOfHealSmall potion;
            inv->reduceItemCount("SmallHeal");
            potion.drinkPotion(player);
        } else if (ch == '2' and inv->getLoot()["MediumHeal"] != 0) {
            PotionOfHealMedium potion;
            inv->reduceItemCount("MediumHeal");
            potion.drinkPotion(player);
        }
        
    }

}


void GameManager::StateHandler() {

    initscr(); // инициализирует библиотеку ncurses и подготавливает терминал к работе
    start_color(); // подключает поддержку цветов
    raw(); // Disble line buffering
    keypad(stdscr, TRUE); // Enable special keys (e.g., function keys)
    noecho(); // Don't echo user input
    curs_set(0); // Hide the cursor

    Inventory inventory;
    Player player(inventory);
    Map map(238, 59, 10);
    while (!gameIsOver()) {
        int interactionNum = map.movePlayer();
        if (interactionNum == 0) {
                setGameOver();
        } else if (interactionNum == 2) {
                clear();
                Chest chest;    
                // printw("CHEST!!!!!!!!!");
                if (chest.returnLoot()[0] == 1) {
                    // PotionOfHealMedium potion;
                    (player.getInventory())->addItem("SmallHeal");
                    // std::cout << typeid(potion).name() << '\n';
                    // printw("medium");

                } else {
                    // PotionOfHealSmall potion;
                    player.getInventory()->addItem("MediumHeal");
                    // std::cout << typeid(potion).name() << '\n';
                    // printw("small");
                }
                // getch();
                chest.displayChest();
                getch();
        } else if (interactionNum == 1) {
                Monster monster = getRandomMonster(player);
                StateBattle battle;
                if(battle.readySetFight(player, monster)) {

                    recieveLoot(player, monster);
                    clear();

                } else {
                    setGameOver();
                };
        } else if (interactionNum == 3) {
            stateInventory(player);

        } else if (interactionNum == 4) {
                Boss boss(player, loopCounter);
                StateBattle battle;
                if(battle.readySetFight(player, boss)) {

                    recieveLoot(player, boss);
                    clear();
                    map = Map(238, 59, 10);
                    increaseLoopCount();

                } else {
                    setGameOver();
                };

        }
    }

    endwin(); // закрытие окошка
}

void GameManager::recieveLoot(Player& player, Monster& monster) {

    int xpToGet = player.getXpLimit() / 10 + rand() % player.getXpLimit() / 10;

    player.addExp(xpToGet);
    player.levelUp();

    bool specialLoot = (rand() % 4) == 0;

    if (specialLoot && monster.getSpriteInd() == "1") {
        player.getInventory()->addItem("SmallHeal"); // дописать для остальных монстров
    }
}

void GameManager::increaseLoopCount() {
    loopCounter+=1;
}