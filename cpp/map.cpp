#include "../h/map.h"

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

void Map::removeChest(int chestInd) {
    chestCoords.erase(chestCoords.begin() + chestInd);
}

void Map::fieldOfView(int y, int x) {

    for (int i = -1; i < 2; i++) {

        if (-2 < i < 2) { 

            for (int j = -2; j < 3; j++) {
                mvprintw(i + y, j + x, "%c", mapLayout[i + y][j + x]);
            }
        }
    }
}

int Map::movePlayer() {

    int x = 1;
    int y = 1;

    for (int i = 0; i < mapHeight; i++) {

        auto playerSearch = (mapLayout[i]).find('@');

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

        int ch = getch();

        if (ch != ERR) {
            
            if (ch == 'q') {
                break;
            } else if (ch == 'f') {

                mapLayout[y][x] = '@';
                return 3;

            } else if (ch == 's' && mapLayout[y + 1][x] != '#') {
                y++;
            } else if (ch == 'a' && mapLayout[y][x - 1] != '#') {
                x--;
            } else if (ch == 'd' && mapLayout[y][x + 1] != '#') {
                x++;
            } else if (ch == 'w' && mapLayout[y - 1][x] != '#') {
                y--;
            }

            if (mapLayout[y][x] == 'E') {

                mapLayout[y][x] = '@';
                return 1;

            } else if (mapLayout[y][x] == 'B') {

                mapLayout[y][x] = '@';
                return 4;

            }

            for (int chest = 0; chest < chestCoords.size(); chest++) {

                if (x == chestCoords[chest].x && y == chestCoords[chest].y) {

                    mapLayout[y][x] = '@';
                    
                    removeChest(chest);

                    return 2;
                }
            }

            displayMap();

            fieldOfView(y, x);

            mvprintw(y, x, "@");

            refresh();

        }

    }

    return 0;
}
