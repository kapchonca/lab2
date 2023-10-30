#include <iostream>
#include <ncurses.h>

void move() {

    initscr(); // инициализирует библиотеку ncurses и подготавливает терминал к работе
    // start_color(); // подключает поддержку цветов
    // raw(); // Disble line buffering
    timeout(0);     // Non-blocking input
    // keypad(stdscr, TRUE); // Enable special keys (e.g., function keys)
    noecho(); // Don't echo user input
    // curs_set(0); // Hide the cursor
    printw("\\o/");

    int x = 0;
    int y = 0;

    while (true) {
        int ch = getch(); // Get the pressed key

        if (ch != ERR) {
            clear();
            // If a key was pressed
            if (ch == 'q') {
                break; // Exit the loop when 'q' is pressed
            } else if (ch == 's') {
                y++;
            } else if (ch == 'a') {
                x--;
            } else if (ch == 'd') {
                x++;
            } else if (ch == 'w') {
                y--;
            }
                mvprintw(y,x,"\\o/");
            refresh();

        }

        // Other actions can be performed here during key press waiting
    }

    endwin(); // Clean up ncurses before exiting

}



int main(int argc, char const *argv[])
{
    /* code */

    move();

    return 0;
}
