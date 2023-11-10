#include "../h/text.h"

void Text::setRandomLine(Monster* monster) { // достает случайную строчку для печати из базы

    std::ifstream dataset("../dataset");

    if (!dataset.is_open()) {
        throw std::invalid_argument( "Couldn't open the file" );
    }

    std::string returnLine;

    srand(time(0)); // обновляем сид функции рандома при помощи текущего времени

    int lineNum = rand() % 50 + 1; // т.к. ранд возвращает большие значения, берем остаток от деления

    for (int i = lineNum + monster->getDatasetOffset(); i > 0; i--) {
        getline(dataset, returnLine); // перебираем строки, пока не дойдем до выпавшей рандомом
    }
    
    lineToPrint = returnLine;

}   

void Text::randomizeLine() {

    for (int i = 0; i < lineToPrint.size(); i++) {

        srand((std::chrono::duration_cast< std::chrono::nanoseconds >(std::chrono::system_clock::now().time_since_epoch()).count()));

        if (rand() % 3 == 0) {

            if (lineToPrint[i] > 96 && lineToPrint[i] < 123) {

                lineToPrint[i] -= 32;

            } else if (lineToPrint[i] > 64 && lineToPrint[i] < 91) {

                lineToPrint[i] += 32;

            }
        }
    }
}

int Text::getTextLength() {
    return textLength;
};

std::string Text::getLineToPrint() {
    return lineToPrint;
};

std::string Text::getLetters() {
    return letters;
};

void Text::setLine(std::string line) {
    this->lineToPrint = line;
}

void Text::setTextLength(int length) {
    this->textLength = length;
}

int Text::operator[](int index) {
    return lineToPrint[index];
}

std::string Text::operator+=(char ch) {
    letters+=ch;
    return letters;
}