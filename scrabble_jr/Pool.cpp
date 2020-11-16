//
// Created by marga on 07/05/2020.
//

#include "Pool.h"

using namespace std;

Pool::Pool(){
};

void Pool::addLettersToPool(vector<vector<Letter>> brd){

    for (int i = 0; i < brd.size(); i++)
        for (int k = 0; k < brd[0].size(); k++)
            if (brd[i][k].getLet() != ' ')
                pl.push_back(brd[i][k].getLet());
}

vector<char> Pool::shuffleLetters(){
    vector <char> letters;
    int rand_index;
    while (letters.size() < 7) {
        rand_index = rand() % pl.size();
        letters.push_back(pl[rand_index]);
        pl.erase(pl.begin() + rand_index);
    }
    return letters;

}

void Pool::sendLetterToPool(char letter){
    pl.push_back(letter);
}

//setters & getters

vector<char> Pool::getPl(){
    return pl;
}

char Pool::getLet(){
    char send;
    int rand_index;
    rand_index = rand() % pl.size();
    send = pl[rand_index];
    pl.erase(pl.begin() + rand_index);
    return send;
}

