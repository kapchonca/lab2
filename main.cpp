#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
// #include <mutex>

static bool s_Finished = false;
static bool s_TimeIsOver = false;

// static std::mutex terminalMutex;

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

class Player {

public:
    int healthMax = 100;
    int healthPoints = 100;
    float attackPoints = 1.0f;
    int level = 1;
    int xp = 0;
    int xpLimit = 100;


};

class Monster {

public:
    int time = 60;
};

void timer(Monster monster) {

    using namespace std::literals::chrono_literals;

    int timePassed = 1;

    while (!s_Finished and (monster.time - ((timePassed-1) / 100)) > 0) {
        // std::lock_guard guard{ terminalMutex };
        // terminalMutex.lock();
        // terminalMutex.lock();
        mvprintw(15,15,"TIME: %d\n", monster.time - ((timePassed-1) / 100));
        // terminalMutex.unlock();
        refresh();
        timePassed++;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    if (!s_Finished) {
    s_TimeIsOver = true;
    }
}



void gaming(std::string text, Player& player, Monster& monster) {

    clear();

    // Start the timer

    std::string letters = ""; // хранит введенные символы
    // std::string word = "";
    
    init_pair(1, COLOR_WHITE, 160); // инициализируем первую цветовую палитру
    init_pair(2, 242, COLOR_BLACK); // инициализируем вторую цветовую палитру
    

    printw("Press 'ESC' to quit.\nFor better experience, turn on fullscreen mode.\n");
    printw("HP: %d/%d\n", player.healthPoints, player.healthMax); // вывод здоровья игрока
    printw("%s\n", text.c_str()); // вывод строки по которой слепопечатаем
    printw("Your line: ");
    refresh();

    std::thread countdown(&timer, monster); // создаем второй поток для независимой работы таймера
    countdown.detach();

    int ch, mistakenChar; //инициализация переменных, хранящих текущий символ и неверно введенный символ соответственно
    int textLength = std::strlen(text.c_str());
    int textIndex = 0;
    int duration = 0;
    while ((textIndex < textLength) && (player.healthPoints > 0) && (!s_TimeIsOver)) {
        bool mistake; 
        ch = getch(); // хватаем введенный символ

        if (ch != ERR) {
            if (ch == 27) { // выход на ESC
                break;
            } else if (ch != text[textIndex]) { // при неверном вводе сохраняем неверный символ
                mistake = true;
                mistakenChar = ch;
                player.healthPoints-=10;
            } else { // иначе добавляем к уже набранной строке и сдвигаем индекс исходной строки на 1
                letters += ch; // Append the character to the letters string
                textIndex++;
            }
        }
        clear();

        printw("Press 'ESC' to quit.\nFor better experience, turn on fullscreen mode.\n");
        printw("HP: %d/%d\n", player.healthPoints, player.healthMax); // вывод здоровья игрока

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

        // Handle other real-time tasks here
    }

    s_Finished = true;
    // countdown.join();
    
}


int main() {

    initscr(); // инициализирует библиотеку ncurses и подготавливает терминал к работе
    start_color(); // подключает поддержку цветов
    Player player;
    Monster monster;
    while (player.healthPoints > 0 and !s_TimeIsOver) {
        std::string text = getRandomLine(); // получаем строку для слепой печати
        gaming(text, player, monster);
        s_Finished = false;
    }

    endwin(); // закрытие окошка


    return 0;
}
