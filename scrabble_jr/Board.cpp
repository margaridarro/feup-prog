//
// Created by marga on 05/05/2020.
//

#include "Board.h"
#include "Word.h"
#include "Letter.h"
#include "common.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


Board::Board() {
}

Board::Board(string name){
    this -> name = name;
    readBoardFile();
}

void Board::buildBoard(){
    brd.resize(lines);
    for (int i = 0; i < lines; i++) {
        brd[i].resize(columns);
    }
    for (int i = 0; i < lines; i++)
        for (int k = 0; k < columns; k++) {
            brd[i][k] = Letter(' ', ' ', 'E', false);
        }
}

void Board::readBoardFile(){
    word_number = 0;
    int word_length, file_line = 0;
    char line, column, direction;
    string str, aux;
    vector<char> word_vec;
    ifstream filestream(name + ".txt");
    stringstream ss;
    if (filestream.is_open()) {
        while (getline(filestream, str)){
            if (str.empty())
                continue;
            if (file_line == 0) {  // reading first file line
                ss = stringstream(str);
                ss >> lines >> aux >> columns;
                buildBoard();
            } else if (str[3] != 'H' && str[3] != 'V' ){
                break;
            } else {
                line = str[0];          // word's first letter line
                column = str[1];        // word's first letter column
                direction = str[3];     // word's direction

                word_length = str.length();
                word_vec.resize(word_length - 5);

                for (int i = 5; i < word_length; i++)
                    word_vec[i - 5] = str[i];

                insertWord(word_vec, line, column, direction);
            }
            file_line++;
        }
    } else { // if opening board fails
        clear();
        setColor(RED, BLACK);
        cout << OPEN_FAILED;
        setColor(WHITE, BLACK);
    }
}

void Board::insertWord(vector <char> word_vec, char line, char column, char direction){
    int l, c;
    bool intersection;
    vector <Letter*> letters_vec;
    l = line - 'A';
    c = column - 'a';

    for (int i = 0; i < word_vec.size() ; i++) {
        intersection = brd[l][c].getState() != 'E'; // state 'E' -> letter part of two different words

        if (i == 0) { // first letter of each word -> state 'P'
            brd[l][c] = Letter(word_vec[i], direction, 'P', intersection);
        } else if (brd[l][c].getState() != 'P') // new letter is not the first of other inserted word -> state 'I'
            brd[l][c] = Letter(word_vec[i], direction, 'I', intersection);

        letters_vec.push_back(&brd[l][c]); // add letters pointer to letters_vec

        if (direction == 'H') c++;
        else l++;
    }

    words_vec.push_back(Word(letters_vec));  // create new object of class Word and add it to words_vec
    word_number++;                           // number of words(maximum of points) is incremented

}

void Board::printBoard(vector <vector<char>> players_options){
    setColor(YELLOW, BLACK);
    cout << "\n\n  ";
    for (int i = 0; i < columns ; i++)
        cout << "  " << char('a' + i);
    cout << "  ";
    for (int i = 0; i < lines ; i++) {
        setColor(YELLOW, BLACK);
        cout << "\n " << char(65 + i) << " ";
        for (int k = 0; k < columns; k++) {
            if (players_options[i][k] == 'P') {
                setColor(GREEN, WHITE);
            }else if (brd[i][k].getState() == 'F') {
                setColor(RED, WHITE);
            } else
                setColor(BLACK, WHITE);
            cout << " " << brd[i][k].getLet() << " ";
        }
    }
    setColor(GREEN, BLACK);
    cout << "\n   Available: Green";
    setColor(RED, BLACK);
    cout << "\n   Permanent: Red\n\n";
    setColor(WHITE, BLACK);
}

void Board::fillLetter(int line, int col) {
    brd[line][col].setState('F'); // F = filled

    // finds next letter to be available in vertical words
    if (brd[line][col].getWord_direction() == 'V' || brd[line][col].getIntersection()) // V = vertical
        for (int i = line + 1; i < brd.size(); i++)
            if (brd[i][col].getState() == 'I') { // I = has letter but it is currrently impossible to be played
                checkUpLeft(i, col);
                break;
            }
    // finds next letter to be available in horizontal words
    if (brd[line][col].getWord_direction() == 'H' || brd[line][col].getIntersection()) // H = horizontal
        for (int i = col + 1; i < brd[0].size(); i++)
            if (brd[line][i].getState() == 'I') { // I = has letter but it is currrently impossible to be played
                checkUpLeft(line, i);
                break;
            }
}

void Board::checkUpLeft(int line, int col) {
    bool setPossibility = true, checkUp = true, checkLeft = true;
    int i = 1;

    while (checkUp || checkLeft) {
        // checks the beginning of a vertical word (up) to see if the letter state can become possible(P)
        if (checkUp && (line - i < 0 || brd[line - i][col].getState() == 'E')) // E = empty
            checkUp = false;
        else if (checkUp && brd[line - i][col].getState() != 'F') // F = filled
            setPossibility = false;
        // checks the beginning of a horizontal word (left) to see if the letter state can become possible(P)
        if (checkLeft && (col - i < 0 || brd[line][col - i].getState() == 'E')) // E = empty
            checkLeft = false;
        else if (checkLeft && brd[line][col - i].getState() != 'F') // F = filled
            setPossibility = false;
        i++;
    }
    if (setPossibility) brd[line][col].setState('P'); // if possible, letter state is set as P
}


//setters & getters

int Board::getWord_number(){
    return word_number;
}

vector<vector<Letter>> Board::getBrd(){
    return brd;
}

vector <Word> Board::getWords_vec(){
    return words_vec;
}