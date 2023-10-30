#include "map.h"
#include <ncurses.h>
#include <iostream>

Map::Map(int width, int height, int roomsCount) {


    ProceduralGeneration new_generation(width, height);
    new_generation.generateMap(roomsCount);

    mapHeight = new_generation.getHeight();
    
    mapLayout.resize(mapHeight);

    // mapLayout = new_generation.getMap();

        // std::string address = "assets/map" + std::to_string(screenNum);
        // std::ifstream file(address);
        // std::string mapLength;
        // getline(file, mapLength); // достаем из начала файла длину спрайта в строчках
        // mapHeight = std::stoi(mapLength);
        // mapLayout.resize(mapHeight);

        for (int i = 0; i < mapHeight; i++) {
            mapLayout[i] = new_generation.getMap()[i];
        }

}


void Map::displayMap() {
    clear();
    for (int i = 0; i < mapHeight; i++) {
        printw("%s", mapLayout[i].c_str()); // вывод спрайта на экран
    }
}

std::vector<std::string> Map::getMapLayout() {
    return mapLayout;
}

// std::vector<int> Map::getNewGeneration() {



// }

int Map::getMapHeight() {
    return mapHeight;
}



int Map::movePlayer() {
    displayMap();
    int x = 1;
    int y = 1;
    for (int i = 0; i < getMapHeight(); i++) {
        auto playerSearch = (getMapLayout()[i]).find('@');
        if (playerSearch != std::string::npos) {
            y = i;
            x = playerSearch;
            mapLayout[y][x] = ' ';
            break;
        }
    }
    while (true) {
        int ch = getch(); // Get the pressed key

        if (ch != ERR) {
            // If a key was pressed
            if (ch == 'q') {
                break; // Exit the loop when 'q' is pressed
            } else if (ch == 's' && getMapLayout()[y + 1][x] != '#') {
                y++;
            } else if (ch == 'a' && getMapLayout()[y][x - 1] != '#') {
                x--;
            } else if (ch == 'd' && getMapLayout()[y][x + 1] != '#') {
                x++;
            } else if (ch == 'w' && getMapLayout()[y - 1][x] != '#') {
                y--;
            }
            if (getMapLayout()[y][x] == '-') {
                srand((std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count()));
                if (rand() % 20 == 0) {
                    mapLayout[y][x] = '@';
                    return 1;
                }
            }
            setCellSeen(y, x);
            displayMap();
            mvprintw(y, x, "@");
            refresh();

        }

        // Other actions can be performed here during key press waiting
    }
    return 0;
}






// void Map::removeEntity(Monster monster) {
//     mapLayout[monster.getPositionY()][monster.getPositionX()] = ' '; // не убирает символ с экрана?
// }

void Map::setCellSeen(int coordY, int coordX) {
    mapLayout[coordY][coordX] = ' ';
}


// // void printSprite(Monster monster) {

// //     std::string address = "sprites/" + monster.spriteInd; // путь к файлу
// //     std::ifstream file(address);
// //     std::string artLength; 
// //     getline(file, artLength); // достаем из начала файла длину спрайта в строчках
// //     int artLengthNum = std::stoi(artLength);

// //     std::string sprite[artLengthNum]; // массив для хранения самого спрайта монстра

// //     for (int i = artLengthNum; i > 0; i--) {
// //         getline(file, sprite[artLengthNum - i]); // считываем файл в массив построчно
// //     }

// //     for (int i = 0; i < 24; i++) {
// //         mvprintw(15 + i, 90, "%s", sprite[i].c_str()); // вывод спрайта на экран
// //     }

// // }



// #include <iostream>
// #include <ncurses.h>
// #include <cstring>
// #include <fstream>
// #include <cstdlib>
// #include <ctime>
// #include <chrono>

// #include <ncurses.h>


// int main() {
//     initscr(); // Initialize ncurses
//     noecho(); // Don't echo user input
//     cbreak(); // Disable line buffering
//     keypad(stdscr, TRUE); // Enable special keys (e.g., function keys)
//     curs_set(0); // Hide the cursor

//     int maxY, maxX;
//     getmaxyx(stdscr, maxY, maxX);

//     // Define the starting position
//     int startY = 0;
//     int startX = 0;

//     std::string artLength;
//     std::string address = "assets/map1";
//     std::ifstream file(address);
//     getline(file, artLength); // достаем из начала файла длину спрайта в строчках
//     int artLengthNum = std::stoi(artLength);
//     std::string sprite[artLengthNum]; // массив для хранения самого спрайта монстра

//     for (int i = artLengthNum; i > 0; i--) {
//         getline(file, sprite[artLengthNum - i]); // считываем файл в массив построчно
//     }

//     for (int i = 0; i < 59; i++) {
//         mvprintw(i, 0, "%s", sprite[i].c_str()); // вывод спрайта на экран
//     }

//     refresh(); // Refresh the screen

//     getch(); // Wait for a key press

//     endwin(); // Terminate ncurses

//     return 0;
// }
