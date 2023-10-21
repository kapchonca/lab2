#include <ncurses.h>

int main() {
    initscr(); // Initialize ncurses
    noecho(); // Don't echo user input
    cbreak(); // Disable line buffering
    keypad(stdscr, TRUE); // Enable special keys (e.g., function keys)
    curs_set(0); // Hide the cursor
    start_color();


    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // инициализируем первую цветовую палитру

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    // Draw the top border
    for (int x = 0; x < maxX; x++) {
        mvaddch(0, x, ACS_HLINE); // Horizontal line character
    }

    // Draw the bottom border
    for (int x = 0; x < maxX; x++) {
        mvaddch(maxY - 1, x, ACS_HLINE); // Horizontal line character
    }

    // Draw the left and right borders
    for (int y = 1; y < maxY - 1; y++) {
        mvaddch(y, 0, ACS_VLINE); // Vertical line character
        mvaddch(y, maxX - 1, ACS_VLINE); // Vertical line character
    }

    // Draw a horizontal line 14 lines from the bottom
    for (int x = 1; x < maxX - 1; x++) {
        mvaddch(maxY - 15, x, ACS_HLINE); // Horizontal line character
    }
    for (int x = 1; x < maxX - 1; x++) {
        mvaddch(11, x, ACS_HLINE); // Horizontal line character
    }

    int centerY = maxY / 2;
    int centerX = maxX / 2;
    const char* monsterArt[24] = {
"                                              ,--,  ,.-.", 
"                ,                   \\,       '-,-`,,-.' | ._", 
"               /|           \\    ,   |\\         }  )/  / `-,',", 
"               [ '          |\\  /|   | |        /  \\|  |/`  ,',", 
"               | |       ,.`  `,` `, | |  _,...(   (      _,", 
"               \\  \\  __ ,-` `  ,  , `/ |,'      Y     (   \\_L\\", 
"                \\  \\_,``,   ` , ,  /  |         )         _,/", 
"                 \\  '  `  ,_ _`_,-,<._.<        /         /", 
"                  ', `>.,`  `  `   ,., |_      |         /", 
"                    \\/`  `,   `   ,`  | /__,.-`    _,   `\\", 
"                -,-..\\  _  \\  `  /  ,  / `._) _, -\\`       \\", 
"                 \\_,,.) /\\    ` /  / ) (-,, ``    ,        |", 
"                ,` )  | \\_\\       '-`  |  `(               \\", 
"               /  /```(   , --, ,' \\   |`<`    ,            |", 
"              /  /_,--`\\   <\\  V /> ,` )<_/)  | \\      _____)", 
"        ,-, ,`   `   (_,\\ \\    |   /) / __/  /   `----`", 
"       (-, \\           ) \\ ('_.-._)/ /,`    /", 
"       | /  `          `/ \\\\ V   V, /`     /", 
"    ,--,\\(        ,     <_/`\\\\     ||      /", 
"   (   ,``-     \\/|         \\-A.A-`|     /", 
"  ,>,_ )_,..(    )\\          -,,_-`  _--`", 
" (_ \\|`   _,/_  /  \\_            ,--`", 
"  \\( `   <.,../`     `-.._   _,-`", 
"   `                  ",

    };

    attron(COLOR_PAIR(1)); // включение цветового паттерна


    // Print the monster ASCII art line by line
    for (int i = 0; i < 24; i++) {
        mvprintw(centerY + i - 12, centerX - 30, "%s", monsterArt[i]);
    }

    attroff(COLOR_PAIR(1)); // его выключение

    mvprintw(3, 118, "AIRAT");
    mvprintw(4, 112, "HP: 91/100 ATK: 7");
    mvprintw(5, 119, "YOU");
    mvprintw(6, 102, "HP: 91/100 ATK: 1.1 LVL: 2 EXP: 15/30");
    mvprintw(7, 112, "REMAINING TIME: 57");
    refresh(); // Refresh the screen

    int ch = getch(); // Wait for a key press

    endwin(); // Terminate ncurses

    return 0;
}

/*
                                              ,--,  ,.-.
                ,                   \,       '-,-`,'-.' | ._
               /|           \    ,   |\         }  )/  / `-,',
               [ '          |\  /|   | |        /  \|  |/`  ,`
               | |       ,.`  `,` `, | |  _,...(   (      _',
               \  \  __ ,-` `  ,  , `/ |,'      Y     (   \_L\
                \  \_\,``,   ` , ,  /  |         )         _,/
                 \  '  `  ,_ _`_,-,<._.<        /         /
                  ', `>.,`  `  `   ,., |_      |         /
                    \/`  `,   `   ,`  | /__,.-`    _,   `\
                -,-..\  _  \  `  /  ,  / `._) _,-\`       \
                 \_,,.) /\    ` /  / ) (-,, ``    ,        |
                ,` )  | \_\       '-`  |  `(               \
               /  /```(   , --, ,' \   |`<`    ,            |
              /  /_,--`\   <\  V /> ,` )<_/)  | \      _____)
        ,-, ,`   `   (_,\ \    |   /) / __/  /   `----`
       (-, \           ) \ ('_.-._)/ /,`    /
       | /  `          `/ \\ V   V, /`     /
    ,--\(        ,     <_/`\\     ||      /
   (   ,``-     \/|         \-A.A-`|     /
  ,>,_ )_,..(    )\          -,,_-`  _--`
 (_ \|`   _,/_  /  \_            ,--`
  \( `   <.,../`     `-.._   _,-`
   `                      ```
*/