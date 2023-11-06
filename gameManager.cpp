

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

void GameManager::stateInventory(Inventory& inventory, Player& player) {
    int ch;
    while (true) {
        inventory.showInventory();
        ch = getch();

        if (ch == 'f') {
            break;
        }

        BasePotionOfHealing potion;
        if (ch == '1' and inventory.getLoot()["SmallHeal"] != 0) {
            PotionOfHealSmall potion;
            inventory.reduceItemCount("SmallHeal");
        } else if (ch == '2' and inventory.getLoot()["MediumHeal"] != 0) {
            PotionOfHealMedium potion;
            inventory.reduceItemCount("MediumHeal");
        }
        potion.drinkPotion(player);
    }

}


void GameManager::StateHandler() {

    initscr(); // инициализирует библиотеку ncurses и подготавливает терминал к работе
    start_color(); // подключает поддержку цветов
    raw(); // Disble line buffering
    keypad(stdscr, TRUE); // Enable special keys (e.g., function keys)
    noecho(); // Don't echo user input
    curs_set(0); // Hide the cursor

    Player player;
    Inventory inventory;
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
                    inventory.addItem("SmallHeal");
                    // std::cout << typeid(potion).name() << '\n';
                    // printw("medium");

                } else {
                    // PotionOfHealSmall potion;
                    inventory.addItem("MediumHeal");
                    // std::cout << typeid(potion).name() << '\n';
                    // printw("small");
                }
                // getch();
                chest.displayChest();
                getch();
        } else if (interactionNum == 1) {
                Monster monster(player);
                StateBattle battle;
                if(battle.readySetFight(player, monster)) {
                    // map.removeEntity(monster);
                    clear();
                    // map.displayMap(); //
                    // // getch(); //
                } else {
                    setGameOver();
                };
        } else if (interactionNum == 3) {
            stateInventory(inventory, player);

        }
    }

    endwin(); // закрытие окошка
}
