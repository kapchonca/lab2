#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "stateBattle.h"

// StateBattle::StateBattle(Player& player, Monster& monster) {
    
// }



void StateBattle::loadInterface(Player& player, Monster& monster) {

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

    // int centerY = maxY / 2;
    // int centerX = maxX / 2;

    mvprintw(2, 118, "%s", monster.getName().c_str()); // выводим все статусы
    mvprintw(3, 111, "HP: %d/%d ATK: %d", monster.getHealthPoints(), monster.getHealthMax(), monster.getAttackPoints());
    mvprintw(6, 119, "YOU");
    mvprintw(7, 111, "HP: %d/%d ATK: %d", player.getHealthPoints(), player.getHealthMax(), player.getAttackPoints());
    mvprintw(8, 112, "REMAINING TIME: ");
    refresh(); 

}


// template <typename Stat>
// Stat getValue(std::string value) {
//     switch (value) {
//         case "heal"
//     }
// }
// template <typename Enemy>
void StateBattle::printSprite(Monster& monster) {

    std::string address = "sprites/" + monster.getSpriteInd(); // путь к файлу
    std::ifstream file(address);
    std::string artLength; 
    getline(file, artLength); // достаем из начала файла длину спрайта в строчках
    int artLengthNum = std::stoi(artLength);

    std::string sprite[artLengthNum]; // массив для хранения самого спрайта монстра

    for (int i = artLengthNum; i > 0; i--) {
        getline(file, sprite[artLengthNum - i]); // считываем файл в массив построчно
    }

    for (int i = 0; i < 26; i++) {
        mvprintw(15 + i, 90, "%s", sprite[i].c_str()); // вывод спрайта на экран
    }

}

std::string StateBattle::randomizeLine(std::string line) {
    for (int i = 0; i < line.size(); i++) {
        srand((std::chrono::duration_cast< std::chrono::nanoseconds >(std::chrono::system_clock::now().time_since_epoch()).count()));
        if (rand() % 3 == 0) {
            if (line[i] > 96 && line[i] < 123) {
                line[i] -= 32;
            } else if (line[i] > 64 && line[i] < 91) {
                line[i] += 32;
            }
        }
    }
    return line;
}

std::string StateBattle::getRandomLine(Monster& monster) { // достает случайную строчку для печати из базы
    std::ifstream dataset("./dataset");

    if (!dataset.is_open()) {
        throw std::invalid_argument( "Couldn't open the file" );
    }

    std::string totalPresets;
    // getline(dataset, totalPresets); // в первой строке файла за 6писано кол-во строчек для выбора 
    // int totalPresetsNum = std::stoi(totalPresets); // конвертация в инт
    std::string returnLine;

    srand(time(0)); // обновляем сид функции рандома при помощи текущего времени
    int lineNum = rand() % 50 + 1; // т.к. ранд возвращает большие значения, берем остаток от деления

    for (int i = lineNum + monster.getDatasetOffset(); i>0; i--) {
        getline(dataset, returnLine); // перебираем строки, пока не дойдем до выпавшей рандомом
    }
    
    return returnLine; 
}   

bool StateBattle::readySetFight(Player& player, Monster& monster) {

    clear();

    std::string letters = ""; // хранит введенные символы
    
    init_pair(1, COLOR_WHITE, 160); // инициализируем первую цветовую палитру
    init_pair(2, 242, COLOR_BLACK); // инициализируем вторую цветовую палитру
    
    loadInterface(player, monster);

    auto start = std::chrono::steady_clock::now(); // начало счетчика времени

    int ch; //инициализация переменных, хранящих текущий символ и неверно введенный символ соответственно


    int textLength = 0;
    int textIndex = 0;
    int duration = 0;
    int timePassed = 0;
    std::string text;



    mvprintw(48, 115, "YOUR LINE:");
    refresh();


    while ((player.getHealthPoints() > 0) && (monster.getTime() - timePassed > 0) && (monster.getHealthPoints() > 0)) {

        if (textIndex == textLength) {
            text = getRandomLine(monster);
            textLength = std::strlen(text.c_str());
            textIndex = 0;
        }

        auto end = std::chrono::steady_clock::now(); // каждый раз обновляем время

        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        timePassed = elapsedTime.count(); // приводит тип к инту

        mvprintw(8, 128,"%d\n", monster.getTime() - timePassed); // вывод времени
        refresh();

        bool mistake; 

        timeout(1000); // если в течение секунды пользователь не нажал кнопку, то скипаем getch() (нужно для корректной работы таймера)

        ch = getch(); // хватаем введенный символ

        if (ch != ERR) { // проверка, если кнопка все же была нажата
            if (ch == 27) { // выход на ESC
                break;
            } else if (ch != text[textIndex]) { // при неверном вводе сохраняем неверный символ
                mistake = true;
                player.decreaseHealth(monster.getAttackPoints());
            } else { // иначе добавляем к уже набранной строке и сдвигаем индекс исходной строки на 1
                letters += ch; // добавляем символ к строке
                textIndex++;
                monster.decreaseHealth(player.getAttackPoints());
            }
        }
        clear();


        if (monster.getRandomizeActive() && (timePassed % 5) == 0) {
            text = randomizeLine(text);
        }

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

        loadInterface(player, monster); // печатает интерфейс

    }

    if (monster.getTime() - timePassed < 1 or player.getHealthPoints() < 1) { // проверяем, при каких условиях мы вышли из цикла
        return false; // если закончилось время, то устанавливаем соответствующий флаг
    } 
    else if (monster.getHealthPoints() < 1) { // если закончилось здоровье монстра, то ...
        // monster.setHealthPoints(monster.getHealthMax());
        // player.setHealthPoints(player.getHealthMax());
        return true;
    }
    return true;
}


// int Text::getTextLength() {
//     return textIndex;
// };
// int Text::getTextIndex() {
//     return textIndex;
// };
// std::string Text::getText() {
//     return text;
// };
// std::string Text::getLetters() {
//     return letters;
// };

