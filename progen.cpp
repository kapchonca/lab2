#include <vector>
#include <algorithm>
#include <ncurses.h>
#include <ctime>
#include <iostream>
#include "progen.h"

bool Room::intersect(const Room &r) const {
    return !(r.x >= (x + w) || x >= (r.x + r.w) || r.y >= (y + h) || y >= (r.y + r.h));
}

    
ProceduralGeneration::ProceduralGeneration(int width, int height): m_width(width), m_height(height) {
    m_data.resize(height);
}
void ProceduralGeneration::generateMap(int roomsCount) {
    m_rooms.clear();
    srand(time(0)); // Update the random seed using the current time

    // Continue generating rooms until the desired count is reached
    while (m_rooms.size() < roomsCount) {
        const int w = 20 + rand() % 41;
        const int h = 10 + rand() % 16;

        const Room room = {
            3 + rand() % (m_width - w - 6),
            3 + rand() % (m_height - h - 6),
            w, h
        };

        auto intersect = std::find_if(std::begin(m_rooms), std::end(m_rooms), [&room](const Room &r) {
            return room.intersect(r);
        });

        if (intersect == std::end(m_rooms)) {
            m_rooms.push_back(room);
        }
    }

    m_data.assign(m_height, std::string(m_width, '#'));

    int roomCounter = 0;

    for (const Room &room : m_rooms) {
    // srand(time(0)); // Update the random seed using the current time
        roomCounter++;
        int playerH, playerW;
        char sym;
        switch (roomCounter) {
            case 1:
                playerH = (rand() % (room.h));
                playerW = (rand() % (room.w));
                break;
        }
        for (int x = 0; x < room.w; ++x) {
            for (int y = 0; y < room.h; ++y) {
                sym = '-';
                if (roomCounter == 1 && (y == playerH) && (x == playerW)) {
                    sym = '@';
                }
                m_data[(room.y + y)][(room.x + x)] = sym;
            }
        }
    }

    for (size_t i = 1; i < m_rooms.size(); ++i) {
        generatePassage(Point{m_rooms[i - 1].x, m_rooms[i - 1].y},
                        Point{m_rooms[i].x, m_rooms[i].y});
    }
}



void ProceduralGeneration::generatePassage(const Point &start, const Point &finish) {
    int x = start.x;
    int y = start.y;

    while (x != finish.x || y != finish.y) {
        if (m_data[y][x] != '@') {
            m_data[y][x] = '-'; // Create a passage at this point
        }
        int dx = 0;
        int dy = 0;

        if (x < finish.x) {
            dx = 1;
        } else if (x > finish.x) {
            dx = -1;
        } else if (y < finish.y) {
            dy = 1;
        } else if (y > finish.y) {
            dy = -1;
        }

        x += dx;
        y += dy;
    }
}

int ProceduralGeneration::getHeight() {
    return m_height;
}


std::vector<std::string> ProceduralGeneration::getMap() {
    return m_data;
}
