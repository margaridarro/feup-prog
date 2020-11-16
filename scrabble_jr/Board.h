//
// Created by marga on 05/05/2020.
//

#ifndef SCRABBLE_JR_BOARD_H
#define SCRABBLE_JR_BOARD_H

#include <iostream>
#include <vector>
#include <string>

#include "Word.h"
#include "Pool.h"
#include "Player.h"
#include "Letter.h"


class Board {
    std::string name;   // board file name which is given by the user
    int lines;          // lines from board file
    int columns;        // columns from board file
    int word_number;    // number of words in the board / maximum of points players can get
    std::vector <std::vector <Letter>> brd;  // board vector of Letter objects
    std::vector <Word> words_vec;            // vector of all words in the board

    //function

    /*
     * resizes board vector according to file information
     * sets every position to empty and intersection to false
     */
    void buildBoard();

    /*
     * reads board file
     * calls buildBoard() after reading the first line
     * calls insertWord() after reading every other line
     * prints a warning if the file fails to open
     */
    void readBoardFile();

    /*
    *  creates Word objects and inserts them in words_vec
    *  inserts Letter objects in board vector from Board class
    *  each Word object takes as arguments pointers to its Letter objects
    */
    void insertWord(std::vector <char> vec, char line, char column, char direction);
public:
    // constructors
    Board();
    Board(std::string name);

    // functions

    /*
     * prints the board
     * prints informative label about the colors of the letters
     */
    void printBoard(std::vector <std::vector<char>> players_options);

    /*
     *  sets chosen letter as 'F' (filled)
     *  calls checkUpLeft()
     */
    void fillLetter(int move_line, int move_col);

    /*
     * Checks all letters of a word with smaller index to the one in question
     * If it gets they are filled, the letter state is set as P
     */
    void checkUpLeft(int line, int col);

    //getters & setters

    int getWord_number();
    std::vector<std::vector<Letter>> getBrd();
    std::vector <Word> getWords_vec();
};


#endif //SCRABBLE_JR_BOARD_H
