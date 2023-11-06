#include <string>
#include <vector>
#include <chrono>
#include "monster.h"
#include "progen.h"

#ifndef MAP
#define MAP



class Map {

protected:
    int mapHeight = 0;
    std::vector<std::string> mapLayout; 
    std::vector<std::string> mapFogLayout; 
    std::vector<Point> chestCoords;
    

public:
    Map(int width, int height, int roomsCount);
    void displayMap();
    int movePlayer();
    std::vector<std::string> getMapLayout();
    std::vector<std::string> getMapFogLayout();

    // std::vector<int> getNewGeneration();
    
    void removeEntity(Monster monster);

    int getMapHeight();

    void setCellSeen(int coordY, int coordX);

    void removeChest(int chestInd);

    void fieldOfView(int y, int x);

};

#endif //MAP