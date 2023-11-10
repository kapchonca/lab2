
#include "../h/stateBattle.h"

void StateBattle::loadInterface(Player* player, Monster* monster) {

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

    mvprintw(2, 118, "%s", monster->getName().c_str()); // выводим все статусы
    mvprintw(3, 111, "HP: %d/%d ATK: %d", monster->getHealthPoints(), monster->getHealthMax(), monster->getAttackPoints());
    mvprintw(6, 119, "YOU");
    mvprintw(7, 111, "HP: %d/%d ATK: %d", player->getHealthPoints(), player->getHealthMax(), player->getAttackPoints());
    mvprintw(8, 112, "REMAINING TIME: ");
    refresh(); 

}


void StateBattle::printSprite(Monster* monster) {

    std::string address = "../sprites/" + monster->getSpriteInd(); // путь к файлу
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

bool StateBattle::readySetFight(Player* player, Monster* monster) {

    clear();
    
    init_pair(1, COLOR_WHITE, 160); // инициализируем первую цветовую палитру
    init_pair(2, 242, COLOR_BLACK); // инициализируем вторую цветовую палитру
    
    loadInterface(player, monster);

    int ch; //инициализация переменных, хранящих текущий символ и неверно введенный символ соответственно

    int textIndex = 0;
    int passedTime = 0;
    
    Timer timer;
    Text text;

    mvprintw(48, 115, "YOUR LINE:");
    refresh();


    while ((player->getHealthPoints() > 0) && (monster->getTime() - passedTime > 0) && (monster->getHealthPoints() > 0)) {

        if (textIndex == text.getTextLength()) {

            text.setRandomLine(monster);
            text.setTextLength(std::strlen(text.getLineToPrint().c_str()));
            textIndex = 0;
            
        }

        passedTime = timer.getPassedTime();

        mvprintw(8, 128,"%d\n", monster->getTime() - passedTime); // вывод времени
        refresh();

        bool mistake; 

        timeout(1000); // если в течение секунды пользователь не нажал кнопку, то скипаем getch() (нужно для корректной работы таймера)

        ch = getch(); // хватаем введенный символ

        if (ch != ERR) { // проверка, если кнопка все же была нажата

            if (ch == 27) { // выход на ESC
                break;

            } else if (ch != text[textIndex]) { // при неверном вводе сохраняем неверный символ

                mistake = true;
                player->decreaseHealth(monster->getAttackPoints());

            } else { // иначе добавляем к уже набранной строке и сдвигаем индекс исходной строки на 1

                text += ch; // добавляем символ к строке
                textIndex++;
                monster->decreaseHealth(player->getAttackPoints());

            }
        }
        clear();


        if (monster->getRandomizeActive() && (passedTime % 5) == 0) {
            text.randomizeLine();
        }

        int maxY, maxX;
        getmaxyx(stdscr, maxY, maxX);
        int centerY = maxY / 2;
        int centerX = maxX / 2;

        move(48, centerX - text.getTextLength() / 2); //двигаем курсор в центр нижнего блока



        attron(COLOR_PAIR(2)); // включение цветового паттерна

        printw("%s", text.getLineToPrint().substr(0,textIndex).c_str()); //вывод уже введенных символов

        attroff(COLOR_PAIR(2)); // его выключение

        if (mistake) {

            attron(COLOR_PAIR(1)); 
            printw("%c", text[textIndex]); // при неверно введенном символе подсвечиваем текущий символ оригинальной строки
            attroff(COLOR_PAIR(1));

            mistake = false; 

        } else {
            printw("%c", text[textIndex]); // иначе все как есть
        }

        if (textIndex != text.getTextLength()) {
            printw("%s\n", text.getLineToPrint().substr(textIndex + 1, text.getTextLength()).c_str()); // вывод еше не введенных символов
        }

        printSprite(monster); // печатает спрайт монстра

        loadInterface(player, monster); // печатает интерфейс

    }

    if (monster->getTime() - passedTime < 1 or player->getHealthPoints() < 1) { // проверяем, при каких условиях мы вышли из цикла
        return false; // если закончилось время, то устанавливаем соответствующий флаг
    } 
    else if (monster->getHealthPoints() < 1) { // если закончилось здоровье монстра, то победка
        return true;
    }

    return true;
}

