// #include <ncurses.h>

// int main() {
//     initscr(); // Initialize ncurses
//     noecho(); // Don't echo user input
//     cbreak(); // Disable line buffering
//     keypad(stdscr, TRUE); // Enable special keys (e.g., function keys)
//     curs_set(0); // Hide the cursor
//     start_color();


//     init_pair(1, COLOR_YELLOW, COLOR_BLACK); // инициализируем первую цветовую палитру

//     int maxY, maxX;
//     getmaxyx(stdscr, maxY, maxX);

//     // Draw the top border
//     for (int x = 0; x < maxX; x++) {
//         mvaddch(0, x, ACS_HLINE); // Horizontal line character
//     }

//     // Draw the bottom border
//     for (int x = 0; x < maxX; x++) {
//         mvaddch(maxY - 1, x, ACS_HLINE); // Horizontal line character
//     }

//     // Draw the left and right borders
//     for (int y = 1; y < maxY - 1; y++) {
//         mvaddch(y, 0, ACS_VLINE); // Vertical line character
//         mvaddch(y, maxX - 1, ACS_VLINE); // Vertical line character
//     }

//     // Draw a horizontal line 14 lines from the bottom
//     for (int x = 1; x < maxX - 1; x++) {
//         mvaddch(maxY - 15, x, ACS_HLINE); // Horizontal line character
//     }
//     for (int x = 1; x < maxX - 1; x++) {
//         mvaddch(11, x, ACS_HLINE); // Horizontal line character
//     }

//     int centerY = maxY / 2;
//     int centerX = maxX / 2;
//     const char* monsterArt[24] = {
// "                                              ,--,  ,.-.", 
// "                ,                   \\,       '-,-`,,-.' | ._", 
// "               /|           \\    ,   |\\         }  )/  / `-,',", 
// "               [ '          |\\  /|   | |        /  \\|  |/`  ,',", 
// "               | |       ,.`  `,` `, | |  _,...(   (      _,", 
// "               \\  \\  __ ,-` `  ,  , `/ |,'      Y     (   \\_L\\", 
// "                \\  \\_,``,   ` , ,  /  |         )         _,/", 
// "                 \\  '  `  ,_ _`_,-,<._.<        /         /", 
// "                  ', `>.,`  `  `   ,., |_      |         /", 
// "                    \\/`  `,   `   ,`  | /__,.-`    _,   `\\", 
// "                -,-..\\  _  \\  `  /  ,  / `._) _, -\\`       \\", 
// "                 \\_,,.) /\\    ` /  / ) (-,, ``    ,        |", 
// "                ,` )  | \\_\\       '-`  |  `(               \\", 
// "               /  /```(   , --, ,' \\   |`<`    ,            |", 
// "              /  /_,--`\\   <\\  V /> ,` )<_/)  | \\      _____)", 
// "        ,-, ,`   `   (_,\\ \\    |   /) / __/  /   `----`", 
// "       (-, \\           ) \\ ('_.-._)/ /,`    /", 
// "       | /  `          `/ \\\\ V   V, /`     /", 
// "    ,--,\\(        ,     <_/`\\\\     ||      /", 
// "   (   ,``-     \\/|         \\-A.A-`|     /", 
// "  ,>,_ )_,..(    )\\          -,,_-`  _--`", 
// " (_ \\|`   _,/_  /  \\_            ,--`", 
// "  \\( `   <.,../`     `-.._   _,-`", 
// "   `                  ",

//     };

//     attron(COLOR_PAIR(1)); // включение цветового паттерна


//     // Print the monster ASCII art line by line
//     for (int i = 0; i < 24; i++) {
//         mvprintw(centerY + i - 12, centerX - 30, "%s", monsterArt[i]);
//     }

//     attroff(COLOR_PAIR(1)); // его выключение

//     mvprintw(3, 118, "AIRAT");
//     mvprintw(4, 112, "HP: 91/100 ATK: 7");
//     mvprintw(5, 119, "YOU");
//     mvprintw(6, 102, "HP: 91/100 ATK: 1.1 LVL: 2 EXP: 15/30");
//     mvprintw(7, 112, "REMAINING TIME: 57");
//     refresh(); // Refresh the screen

//     int ch = getch(); // Wait for a key press

//     endwin(); // Terminate ncurses

//     return 0;
// }

// /*
//                                               ,--,  ,.-.
//                 ,                   \,       '-,-`,'-.' | ._
//                /|           \    ,   |\         }  )/  / `-,',
//                [ '          |\  /|   | |        /  \|  |/`  ,`
//                | |       ,.`  `,` `, | |  _,...(   (      _',
//                \  \  __ ,-` `  ,  , `/ |,'      Y     (   \_L\
//                 \  \_\,``,   ` , ,  /  |         )         _,/
//                  \  '  `  ,_ _`_,-,<._.<        /         /
//                   ', `>.,`  `  `   ,., |_      |         /
//                     \/`  `,   `   ,`  | /__,.-`    _,   `\
//                 -,-..\  _  \  `  /  ,  / `._) _,-\`       \
//                  \_,,.) /\    ` /  / ) (-,, ``    ,        |
//                 ,` )  | \_\       '-`  |  `(               \
//                /  /```(   , --, ,' \   |`<`    ,            |
//               /  /_,--`\   <\  V /> ,` )<_/)  | \      _____)
//         ,-, ,`   `   (_,\ \    |   /) / __/  /   `----`
//        (-, \           ) \ ('_.-._)/ /,`    /
//        | /  `          `/ \\ V   V, /`     /
//     ,--\(        ,     <_/`\\     ||      /
//    (   ,``-     \/|         \-A.A-`|     /
//   ,>,_ )_,..(    )\          -,,_-`  _--`
//  (_ \|`   _,/_  /  \_            ,--`
//   \( `   <.,../`     `-.._   _,-`
//    `                      ```
// */


// #include <vector>
// #include <iostream>
// #include <string>

// int main(int argc, char const *argv[])
// {
//     std::vector<std::string> a;
//     a.resize(1);
//     a[0] = "asdaasd";
//     a[0][2] = '!';
//     std::cout << a[0];
//     return 0;
// }

#include <vector>
#include <algorithm>
#include <ncurses.h>
#include <ctime>
#include <string>
#include "progen.h"

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

    for (const Room &room : m_rooms) {
        for (int x = 0; x < room.w; ++x) {
            for (int y = 0; y < room.h; ++y) {
                m_data[(room.y + y)][(room.x + x)] = ' ';
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
        m_data[y][x] = ' '; // Create a passage at this point

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

int main(int argc, char const *argv[]) {
    // Initialize ncurses and set up the terminal
    initscr();
    int width = 238;
    int height = 59;
    int roomsCount = 10;
    ProceduralGeneration map(width, height);
    map.generateMap(roomsCount);
    // Display the map on the terminal using ncurses
    for (int i = 0; i < map.getHeight(); i++) {
        printw("%s", map.getMap()[i].c_str());
    }
    refresh();
    getch();
    endwin(); // Close the ncurses window
    return 0;
}
