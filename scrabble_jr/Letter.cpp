//
// Created by marga on 12/05/2020.
//

#include "Letter.h"

Letter::Letter(){
}

Letter::Letter(char let, char word_direction, char state, bool intersection){
    this -> let = let;
    this -> word_direction = word_direction;
    this -> intersection = intersection;
    this -> state = state; // P = possible/unfilled || I = impossible || E = empty || F = filled/permanent
}

char Letter::getLet() {
    return let;
}

char Letter::getWord_direction() {
    return word_direction;
}

char Letter::getState(){
    return state;
}

void Letter::setState(char s){
    state = s;
}

bool Letter::getIntersection() {
    return intersection;
}
