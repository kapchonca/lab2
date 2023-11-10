#include "../h/chest.h"

Chest::Chest() {

    srand(time(0));
    
    loot.push_back(rand() % 4 + 1);
    
}

std::vector<int> Chest::returnLoot() {
    return loot;
}

void Chest::displayChest() {

    mvprintw(10, 120, "YOU FOUND A CHEST");

    
    std::string address = "../sprites/chest"; // путь к файлу
    std::ifstream file(address);

    std::string sprite[18]; // массив для хранения самого спрайта монстра

    for (int i = 18; i > 0; i--) {
        getline(file, sprite[18 - i]); // считываем файл в массив построчно
    }

    for (int i = 20; i < 38; i++) {
        mvprintw(i, 90, "%s", sprite[i-20].c_str()); // вывод спрайта на экран
    }
}