//
// Created by marga on 15/05/2020.
//

#include "common.h"

#include <iostream>
#include <Windows.h>

using namespace std;

void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

void clear(){
    cout << flush;
    system("CLS");
}

void clearCin() {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}


