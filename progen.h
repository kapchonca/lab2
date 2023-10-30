#ifndef PROGEN
#define PROGEN

#include <vector>
#include <algorithm>
#include <ncurses.h>
#include <ctime>
#include <string>

struct Point {
    int x, y;
};
struct Room {
    int x, y, w, h;
    bool intersect(const Room &r) const;
};


class ProceduralGeneration {
private:
    int m_width, m_height;     // размеры карты
    std::vector<std::string> m_data;   // финальные данные карты
    std::vector<Room> m_rooms; // комнаты

public:
ProceduralGeneration(int width, int height);


void generateMap(int roomsCount);



void generatePassage(const Point &start, const Point &finish);

int getHeight();

std::vector<std::string> getMap();

};



#endif //PROGEN