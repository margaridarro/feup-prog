//
// Created by marga on 06/05/2020.
//
#include "Word.h"

using namespace std;

Word::Word(vector<Letter*> letters_vec){
    this -> letters_vec = letters_vec;
    this -> complete;
}

void Word::updateComplete(){
    complete = true;
    for (Letter *let : letters_vec)
        if (let -> getState() != 'F') {
            complete = false;
            break;
        }
}


//getters & setters

bool Word::getComplete(){
    return complete;
}

