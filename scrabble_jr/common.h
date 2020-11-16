//
// Created by marga on 15/05/2020.
//

#ifndef SCRABBLE_JR_COMMON_H
#define SCRABBLE_JR_COMMON_H

#include <string>

#define BLACK 0
#define GREEN 2
#define RED 4
#define MAGENTA 5
#define LIGHTCYAN 11
#define YELLOW 14
#define WHITE 15

// main
#define WELCOME "\n W E L C O M E  T O  S C R A B B L E  J U N I O R  G A M E ! \n\n";
#define CHOOSING_BOARD "Choose a board by entering its name, make sure it's in the same folder as this program (e.g. 'Board')\n"
#define PLAY_AGAIN "Would you like to play again?(y/n)\n"

// Board
#define BOARD_ERROR "Enter another board with at least 14 letters.\n If you'd like to quit playing enter '/quit' instead of the new board name.\n"
#define SUITABLE_BOARD "This board is only suitable for a "
#define PROCEED "-player game, do you wish to continue with this board?(y/n)\n"
#define OPEN_FAILED "Failed to open the board file.\n"

// Game
#define NO_LETTERS_AVAILABLE ", you have no letters available to be played.\nInstead of playing, choose"
#define OUT_OF_MOVES " doesn't have any other move available.\n"
#define MAKE_MOVE " make your move (e.g. Bd)\n"
#define MULTIPLE_WINNERS "\n\nThe winners are:\n"
#define ONE_WINNER "\n\nThe winner is "


void setColor(int textColor, int bgColor);

void clear();

void clearCin();


#endif //SCRABBLE_JR_COMMON_H
