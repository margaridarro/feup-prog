//
// Created by marga on 06/05/2020.
//

#include "Player.h"

using namespace std;

Player::Player(){
};


Player::Player(string name, int score, vector<char> letters, int color){
    this -> name = name;
    this -> score = score;
    this -> letters = letters; //7 per player
    this -> color = color;
};

// setters & getters

int Player::getScore() {
    return score;
}
void Player::setScore(int s){
    score = s;
}

string Player::getName(){
    return name;
}

vector<char> Player::getLetters(){
    return letters;
}
void Player::setLetters(vector <char> let){
    letters = let;
}

int Player::getColor() {
    return color;
}