//
// Created by marga on 07/05/2020.
//

#ifndef SCRABBLE_JR_POOL_H
#define SCRABBLE_JR_POOL_H

#include <iostream>
#include <vector>

#include "Word.h"
#include "Board.h"
#include "Letter.h"


class Pool {
    std::vector <char> pl; // vector of letters
public:
    // constructor
    Pool();

    // functions

    /*
     * called when after board file
     * called when player wants to exchanges letters with the pool
     */
    void addLettersToPool(std::vector<std::vector<Letter>> brd);

    /*
     * returns a vector of 7 random letters to each player in the beginning of the game
     */
    std::vector<char> shuffleLetters();

    /*
     * sends 1 letter and erases it from the pool
     */
    void sendLetterToPool(char letter);


    //getters & setters
    std::vector<char> getPl();
    char getLet();
};


#endif //SCRABBLE_JR_POOL_H
