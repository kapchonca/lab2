
#include "monster.h"
#include "player.h"

#ifndef STATEBATTLE
#define STATEBATTLE

// #include <string>

class StateBattle {

// private:
//     Player *p_player; 
//     Monster *p_monster;

public:

    // StateBattle(Player& player, Monster& monster);

    void loadInterface(Player& player, Monster& monster);
    // template <typename Enemy>
    void printSprite(Monster& monster);
    std::string getRandomLine(Monster& monster);
    bool readySetFight(Player& player, Monster& monster);
    std::string randomizeLine(std::string line);
    void displaySentence();
};

// class Text {
// protected:
//     int textLength = 0;
//     int textIndex = 0;
//     std::string text;
//     std::string letters = ""; // хранит введенные символы

// public:

//     int getTextLength();
//     int getTextIndex();
//     std::string getText();
//     std::string getLetters();

// };



#endif //STATEBATTLE