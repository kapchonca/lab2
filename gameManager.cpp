

#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "gameManager.h"

// void GameManager::loadInterface(Player& player, Monster& monster) {

//     int maxY, maxX;
//     getmaxyx(stdscr, maxY, maxX); // получаем измерения окна

//     for (int x = 0; x < maxX; x++) {
//         mvaddch(0, x, ACS_HLINE); // горизонтальная линия сверху
//     }

//     for (int x = 0; x < maxX; x++) {
//         mvaddch(maxY - 1, x, ACS_HLINE); // горизонтальная линия снизу
//     }

//     for (int y = 1; y < maxY - 1; y++) {
//         mvaddch(y, 0, ACS_VLINE); // вертикальные линии по бокам
//         mvaddch(y, maxX - 1, ACS_VLINE); 
//     }

//     for (int x = 1; x < maxX - 1; x++) {
//         mvaddch(maxY - 15, x, ACS_HLINE); // линия, отделяющая блок с текстом
//     }
//     for (int x = 1; x < maxX - 1; x++) {
//         mvaddch(11, x, ACS_HLINE); // линия, отделяющая блок со статусами
//     }

//     // int centerY = maxY / 2;
//     // int centerX = maxX / 2;

//     mvprintw(2, 118, "%s", monster.getName().c_str()); // выводим все статусы
//     mvprintw(3, 111, "HP: %d/%d ATK: %d", monster.getHealthPoints(), monster.getHealthMax(), monster.getAttackPoints());
//     mvprintw(6, 119, "YOU");
//     mvprintw(7, 111, "HP: %d/%d ATK: %d", player.getHealthPoints(), player.getHealthMax(), player.getAttackPoints());
//     mvprintw(8, 112, "REMAINING TIME: ");
//     refresh(); 

// }

bool GameManager::gameIsOver() {
    if (s_GameIsOver) {
        return true;
    } else {
        return false;
    }
}

// void GameManager::printSprite(Monster monster) {

//     std::string address = "sprites/" + monster.getSpriteInd(); // путь к файлу
//     std::ifstream file(address);
//     std::string artLength; 
//     getline(file, artLength); // достаем из начала файла длину спрайта в строчках
//     int artLengthNum = std::stoi(artLength);

//     std::string sprite[artLengthNum]; // массив для хранения самого спрайта монстра

//     for (int i = artLengthNum; i > 0; i--) {
//         getline(file, sprite[artLengthNum - i]); // считываем файл в массив построчно
//     }

//     for (int i = 0; i < 26; i++) {
//         mvprintw(15 + i, 90, "%s", sprite[i].c_str()); // вывод спрайта на экран
//     }

// }

void GameManager::setGameOver() {
    s_GameIsOver = true;
}

// std::string GameManager::getRandomLine() { // достает случайную строчку для печати из базы
//     std::ifstream dataset("./dataset");

//     if (!dataset.is_open()) {
//         throw std::invalid_argument( "Couldn't open the file" );
//     }

//     std::string totalPresets;
//     getline(dataset, totalPresets); // в первой строке файла за 6писано кол-во строчек для выбора 
//     int totalPresetsNum = std::stoi(totalPresets); // конвертация в инт
//     std::string returnLine;

//     srand(time(0)); // обновляем сид функции рандома при помощи текущего времени
//     int lineNum = rand() % totalPresetsNum + 1; // т.к. ранд возвращает большие значения, берем остаток от деления

//     for (int i = lineNum; i>0; i--) {
//         getline(dataset, returnLine); // перебираем строки, пока не дойдем до выпавшей рандомом
//     }
    
//     return returnLine; 
// }   

// void GameManager::StateIdle(Player& player, Monster& monster) {
//     Map map(1);
//     int interaction =  map.movePlayer();
//     while (true) {
//         switch (interaction) {
//             case 1:
//                 if(StateBattle(player, monster)) {
//                     map.removeEntity(monster);
//                     clear();
//                     map.displayMap(); //
//                     getch(); //
//                 };
//         }
//     }
// }

void GameManager::StateHandler() {

    initscr(); // инициализирует библиотеку ncurses и подготавливает терминал к работе
    start_color(); // подключает поддержку цветов
    raw(); // Disble line buffering
    keypad(stdscr, TRUE); // Enable special keys (e.g., function keys)
    noecho(); // Don't echo user input
    curs_set(0); // Hide the cursor

    Player player;
    Map map(238, 59, 10);
    while (!gameIsOver()) {
        int interactionNum = map.movePlayer();
        switch (interactionNum) {
            case 0:
                setGameOver();
                break;
            case 1:
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
                break;
        }
    }

    endwin(); // закрытие окошка
}
