#include "map.h"
#include <ncurses.h>
#include <iostream>

Map::Map(int width, int height, int roomsCount) {


    ProceduralGeneration new_generation(width, height);
    new_generation.generateMap(roomsCount);

    mapHeight = new_generation.getHeight();
    
    mapLayout.resize(mapHeight);
    mapFogLayout.resize(mapHeight);

    chestCoords = new_generation.getChestsCoords();


    for (int i = 0; i < mapHeight; i++) {
        mapLayout[i] = new_generation.getMap()[i];
    }
    for (int i = 0; i < mapHeight; i++) {
        mapFogLayout[i] = new_generation.getMapFog()[i];
    }


}


void Map::displayMap() {
    clear();
    for (int i = 0; i < mapHeight; i++) {
        printw("%s", mapFogLayout[i].c_str()); // вывод спрайта на экран
    }
}

std::vector<std::string> Map::getMapLayout() {
    return mapLayout;
}

std::vector<std::string> Map::getMapFogLayout() {
    return mapFogLayout;
}
// std::vector<int> Map::getNewGeneration() {



// }

int Map::getMapHeight() {
    return mapHeight;
}

void Map::removeChest(int chestInd) {
    chestCoords.erase(chestCoords.begin() + chestInd);
}

void Map::fieldOfView(int y, int x) {
    for (int i = -1; i < 2; i++) {
        if (-2 < i < 2) { //
            for (int j = -2; j < 3; j++) {
                mvprintw(i + y, j + x, "%c", mapLayout[i + y][j + x]);
            }
        } 
        // else {
        //     for (int j = -1; j < 2; j++) {
        //         if (mapLayout[i + y][j + x] == '-'){ 
        //             mapLayout[i + y][j + x] = ' ';
        //         }
        //     }
        // }
    }
}

int Map::movePlayer() {
    int x = 1;
    int y = 1;
    for (int i = 0; i < getMapHeight(); i++) {
        auto playerSearch = (getMapLayout()[i]).find('@');
        if (playerSearch != std::string::npos) {
            y = i;
            x = playerSearch;
            mapFogLayout[y][x] = '-';
            mapLayout[y][x] = ' ';
            break;
        }
    }
    displayMap();

    fieldOfView(y, x);
    mvprintw(y, x, "@");

    while (true) {

        int ch = getch(); // Get the pressed key

        if (ch != ERR) {
            // If a key was pressed
            if (ch == 'q') {
                break; // Exit the loop when 'q' is pressed
            } else if (ch == 'f') {
                mapLayout[y][x] = '@';
                return 3;
            } else if (ch == 's' && getMapLayout()[y + 1][x] != '#') {
                y++;
            } else if (ch == 'a' && getMapLayout()[y][x - 1] != '#') {
                x--;
            } else if (ch == 'd' && getMapLayout()[y][x + 1] != '#') {
                x++;
            } else if (ch == 'w' && getMapLayout()[y - 1][x] != '#') {
                y--;
            }


            // srand((std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count()));
            // if (rand() % 35 == 0) {
            //     mapLayout[y][x] = '@';
            //     return 1;
            // }
            if (mapLayout[y][x] == 'E') {
                mapLayout[y][x] = '@';
                return 1;
            }

            for (int chest = 0; chest < chestCoords.size(); chest++) {
                if (x == chestCoords[chest].x && y == chestCoords[chest].y) {
                    mapLayout[y][x] = '@';
                    
                    removeChest(chest);

                    return 2;
                }
            }


            // setCellSeen(y, x);
            displayMap();
            fieldOfView(y, x);
            mvprintw(y, x, "@");
            refresh();

        }

        // Other actions can be performed here during key press waiting
    }
    return 0;
}


// void Map::setCellSeen(int coordY, int coordX) {
//     mapLayout[coordY][coordX] = ' ';
// }
