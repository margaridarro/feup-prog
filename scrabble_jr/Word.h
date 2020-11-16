//
// Created by marga on 06/05/2020.
//

#ifndef SCRABBLE_JR_WORD_H
#define SCRABBLE_JR_WORD_H

#include <iostream>
#include <vector>
#include <string>

#include "Letter.h"

class Letter;

class Word{
    std::vector <Letter*> letters_vec;
    bool complete;
public:
    Word(std::vector<Letter*> letters_vec);
    void updateComplete();

    // getters & setters
    bool getComplete();

};



#endif //SCRABBLE_JR_WORD_H
