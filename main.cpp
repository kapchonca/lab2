#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <variant>

static bool s_TimeIsOver = false;


std::string getRandomLine() {  // достает случайную строчку для печати из базы
    std::ifstream dataset("./dataset");

    if (!dataset.is_open()) {
        throw std::invalid_argument( "Couldn't open the file" );
    }

    std::string totalPresets;
    getline(dataset, totalPresets); // в первой строке файла записано кол-во строчек для выбора 
    int totalPresetsNum = std::stoi(totalPresets); // конвертация в инт
    std::string returnLine;

    srand(time(0)); // обновляем сид функции рандома при помощи текущего времени
    int lineNum = rand() % totalPresetsNum + 1; // т.к. ранд возвращает большие значения, берем остаток от деления

    for (int i = lineNum; i>0; i--) {
        getline(dataset, returnLine); // перебираем строки, пока не дойдем до выпавшей рандомом
    }
    
    return returnLine; 
}   

// class gameManager {  надеюсь разобраться и в будущем перенести сюда менеджмент состояний игрока

// public:
//      void stateIdle() {

//      }

//      void stateBattle() {

//      }
// };



class Player {

public:
    int healthMax = 100;
    int healthPoints = 100;
    int attackPoints = 10;
    int level = 1;
    int xp = 0;
    int xpLimit = 100;


};

class Monster {

public:
    int time = 60;
    int healthMax = 1000;
    int healthPoints = 1000;
    int attackPoints = 7;
    std::string name = "AIRAT";
    std::string spriteInd = "1";

};

// class Goblin: public Monster { в будущем появятся классы монстров, пока проверял, все ли работает с дочерними

// };

// class Dragon: public Monster {

// };


void printSprite(Monster monster) {

    std::string address = "sprites/" + monster.spriteInd; // путь к файлу
    std::ifstream file(address);
    std::string artLength; 
    getline(file, artLength); // достаем из начала файла длину спрайта в строчках
    int artLengthNum = std::stoi(artLength);

    std::string sprite[artLengthNum]; // массив для хранения самого спрайта монстра

    for (int i = artLengthNum; i > 0; i--) {
        getline(file, sprite[artLengthNum - i]); // считываем файл в массив построчно
    }

    for (int i = 0; i < 24; i++) {
        mvprintw(15 + i, 90, "%s", sprite[i].c_str()); // вывод спрайта на экран
    }

}

void interface(Player& player, Monster& monster) {

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX); // получаем измерения окна

    for (int x = 0; x < maxX; x++) {
        mvaddch(0, x, ACS_HLINE); // горизонтальная линия сверху
    }

    for (int x = 0; x < maxX; x++) {
        mvaddch(maxY - 1, x, ACS_HLINE); // горизонтальная линия снизу
    }

    for (int y = 1; y < maxY - 1; y++) {
        mvaddch(y, 0, ACS_VLINE); // вертикальные линии по бокам
        mvaddch(y, maxX - 1, ACS_VLINE); 
    }

    for (int x = 1; x < maxX - 1; x++) {
        mvaddch(maxY - 15, x, ACS_HLINE); // линия, отделяющая блок с текстом
    }
    for (int x = 1; x < maxX - 1; x++) {
        mvaddch(11, x, ACS_HLINE); // линия, отделяющая блок со статусами
    }

    int centerY = maxY / 2;
    int centerX = maxX / 2;

    mvprintw(2, 118, "%s", monster.name.c_str()); // выводим все статусы
    mvprintw(3, 111, "HP: %d/%d ATK: %d", monster.healthPoints, monster.healthMax, monster.attackPoints);
    mvprintw(6, 119, "YOU");
    mvprintw(7, 111, "HP: %d/%d ATK: %d", player.healthPoints, player.healthMax, player.attackPoints);
    mvprintw(8, 112, "REMAINING TIME: ");
    refresh(); 

}

// void stateIdle(Player& player, Monster& monster) { следующий шаг разработки
//     interface(player, monster);
// }


void gaming(std::string text, Player& player, Monster& monster) {

    clear();


    std::string letters = ""; // хранит введенные символы
    
    init_pair(1, COLOR_WHITE, 160); // инициализируем первую цветовую палитру
    init_pair(2, 242, COLOR_BLACK); // инициализируем вторую цветовую палитру
    
    interface(player, monster);

    auto start = std::chrono::steady_clock::now(); // начало счетчика времени

    int ch; //инициализация переменных, хранящих текущий символ и неверно введенный символ соответственно


    int textLength = std::strlen(text.c_str());
    int textIndex = 0;
    int duration = 0;
    int timePassed = 0;

    mvprintw(48, 115, "YOUR LINE:");
    refresh();


    while ((textIndex < textLength) && (player.healthPoints > 0) && (monster.time - timePassed > 0) && (monster.healthPoints > 0)) {

        auto end = std::chrono::steady_clock::now(); // каждый раз обновляем время

        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        timePassed = elapsedTime.count(); // приводит тип к инту

        mvprintw(8, 128,"%d\n", monster.time - timePassed); // вывод времени
        refresh();

        bool mistake; 

        timeout(1000); // если в течение секунды пользователь не нажал кнопку, то скипаем getch() (нужно для корректной работы таймера)

        ch = getch(); // хватаем введенный символ

        if (ch != ERR) { // проверка, если кнопка все же была нажать
            if (ch == 27) { // выход на ESC
                break;
            } else if (ch != text[textIndex]) { // при неверном вводе сохраняем неверный символ
                mistake = true;
                // mistakenChar = ch;
                player.healthPoints-=monster.attackPoints;
            } else { // иначе добавляем к уже набранной строке и сдвигаем индекс исходной строки на 1
                letters += ch; // Append the character to the letters string
                textIndex++;
                monster.healthPoints-=player.attackPoints;
            }
        }
        clear();

        int maxY, maxX;
        getmaxyx(stdscr, maxY, maxX);
        int centerY = maxY / 2;
        int centerX = maxX / 2;

        move(48, centerX - textLength / 2); //двигаем курсор в центр нижнего блока



        attron(COLOR_PAIR(2)); // включение цветового паттерна

        printw("%s", text.substr(0,textIndex).c_str()); //вывод уже введенных символов

        attroff(COLOR_PAIR(2)); // его выключение

        if (mistake) {
            attron(COLOR_PAIR(1)); 
            printw("%c", text[textIndex]); // при неверно введенном символе подсвечиваем текущий символ оригинальной строки
            attroff(COLOR_PAIR(1));

            mistake = false; 
        } else {
            printw("%c", text[textIndex]); // иначе все как есть
        }

        if (textIndex != textLength) {
            printw("%s\n", text.substr(textIndex + 1, std::strlen(text.c_str())).c_str()); // вывод еше не введенных символов
        }

        printSprite(monster); // печатает спрайт монстра

        interface(player, monster); // печатает интерфейс

    }

    if (monster.time - timePassed < 1) { // проверяем, при каких условиях мы вышли из цикла
        s_TimeIsOver = true; // если закончилось время, то устанавливаем соответствующий флаг
    } else if (monster.healthPoints < 1) { // если закончилось здоровье монстра, то ...
        monster.healthPoints = monster.healthMax;
        player.healthPoints = player.healthMax;
    }
    
}


int main() {
    

    initscr(); // инициализирует библиотеку ncurses и подготавливает терминал к работе
    start_color(); // подключает поддержку цветов
    raw(); // Disble line buffering
    keypad(stdscr, TRUE); // Enable special keys (e.g., function keys)
    noecho(); // Don't echo user input
    curs_set(0); // Hide the cursor


    Player player;
    Monster monster;

    while (player.healthPoints > 0 and !s_TimeIsOver) {
        std::string text = getRandomLine(); // получаем строку для слепой печати
        gaming(text, player, monster); // запускаем игрульку
    }

    endwin(); // закрытие окошка

    return 0;
}
