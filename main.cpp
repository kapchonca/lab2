#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>

std::string getRandomLine() { 
    std::ifstream dataset("./dataset");
    if (!dataset.is_open()) {
        throw std::invalid_argument( "Couldn't open the file" );
    }

    std::string totalPresets;
    getline(dataset, totalPresets);
    int totalPresetsNum = std::stoi(totalPresets);
    std::string returnLine;

    srand(time(0));
    int lineNum = rand() % totalPresetsNum + 1;

    for (int i = lineNum; i>0; i--) {
        getline(dataset, returnLine);
    }
    
    return returnLine;
}

int main() {
    initscr(); // инициализирует библиотеку ncurses и подготавливает терминал к работе
    start_color(); // подключает поддержку цветов
    // cbreak();
    // noecho();
    // keypad(stdscr, TRUE);
    // nodelay(stdscr, TRUE);

    // std::string input = "";
    std::string letters = ""; // хранит введенные символы
    // std::string word = "";
    std::string text = getRandomLine(); // получаем строку для слепой печати
    
    init_pair(1, COLOR_WHITE, 160); // инициализируем первую цветовую палитру
    init_pair(2, 242, COLOR_BLACK); // инициализируем вторую цветовую палитру
    

    printw("Press 'ESC' to quit.\nFor better experience, turn on fullscreen mode.\n");
    printw("%s\n", text.c_str()); // вывод строки по которой слепопечатаем
    printw("Your line: ");
    refresh();

    int ch, mistakenChar; //инициализация переменных, хранящих текущий символ и неверно введенный символ соответственно
    int textLength = std::strlen(text.c_str());
    int textIndex = 0;
    while (textIndex < textLength) {
        bool mistake; 
        ch = getch(); // хватаем введенный символ

        if (ch != ERR) {
            if (ch == 27) { // выход на ESC
                break;
            } else if (ch != text[textIndex]) { // при неверном вводе сохраняем неверный символ
                mistake = true;
                mistakenChar = ch;
            } else { // иначе добавляем к уже набранной строке и сдвигаем индекс исходной строки на 1
                letters += ch; // Append the character to the letters string
                // word += ch;
                textIndex++;
            }

            clear();

    printw("Press 'ESC' to quit.\nFor better experience, turn on fullscreen mode.\n");

            attron(COLOR_PAIR(2)); // включение цветового паттерна

            printw("%s", text.substr(0,textIndex).c_str()); //вывод уже введенных символов

            attroff(COLOR_PAIR(2)); // его выключение

            printw("%s\n", text.substr(textIndex, std::strlen(text.c_str())).c_str()); // вывод еше не введенных символов

            printw("Your line: %s", letters.c_str()); // вывод введенных символов

            if (mistake) { // при неверном вводе подсвечивает неверно введенный символ
                attron(COLOR_PAIR(1)); 
                printw("%c", ch);
                attroff(COLOR_PAIR(1));

                mistake = false;
            } 
            // printw("Input: %s\n", input.c_str());
        }

        // Handle other real-time tasks here
    }

    endwin(); // закрытие окошка

    // if (!input.empty()) {
    //     std::cout << "You typed: " << input << std::endl;
    // }

    return 0;
}
