#ifndef TIME
#define TIME

#include <fstream>
#include <chrono>

#include "../h/monster.h"

class Text {

protected:

    int textLength = 0;
    
    std::string lineToPrint;

    std::string letters = ""; // хранит введенные символы

public:

    int getTextLength();
    
    std::string getLineToPrint();

    std::string getLetters();

    void setLine(std::string line);

    void setTextLength(int length);
    
    void setRandomLine(Monster* monster);
    
    void randomizeLine();

    int operator[](int index);

    std::string operator+=(char ch);

};

#endif //TIME