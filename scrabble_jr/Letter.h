//
// Created by marga on 12/05/2020.
//

#ifndef SCRABBLE_JR_LETTER_H
#define SCRABBLE_JR_LETTER_H

#include <vector>
#include "Word.h"


class Letter {
    char let;
    char word_direction;
    char state;
    bool intersection;

public:
    // constructors
    Letter();
    Letter(char let, char word_direction, char state, bool intersection);

    // getters & setters
    char getLet();
    char getWord_direction();
    char getState();
    void setState(char s);
    bool getIntersection();

};


#endif //SCRABBLE_JR_LETTER_H
