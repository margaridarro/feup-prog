//
// Created by marga on 08/05/2020.
//

#ifndef SCRABBLE_JR_GAME_H
#define SCRABBLE_JR_GAME_H

#include "Pool.h"
#include "Player.h"
#include "Letter.h"
#include "Board.h"

#include <vector>

class Game {
    std::vector<Player> players_vec;
    std::vector<std::vector<char>> players_options; // sets every available word position to 'P' & used to print board
    Pool pool;
    Board* board;
    bool flag_end_of_game; // false until all words are complete
    int complete_words; // recalculated after every move
    int pre_complete_words; // is compared to complete_words to get players' scores
    int move_line;  // player input
    int move_col;   // player input

    // functions

    /*
     * resizes players_options according to chosen board's size
     */
    void resizePlayers_options();

    /*
     * returns check_possibilities
     * updates players_options for the current player
     */
    int resetPlayers_options(const std::vector <char>& player_letters);

    /*
     * informs player is out of moves
     * prints how many letters can be exchanged
     */
    void printNoMove_ChangeLetters(int turn);

    /*
     * withdraws letter(s) from the pool
     * receives letter(s) input
     * sends them to the pool
     * adds new letters to player_letters
     */
    std::vector <char> changeLettersWithPool(std::vector <char> player_letters);

    /*
     * informs player is out of moves
     * waits a little so the message isn't lost
     */
    void printNoMove_NoChangeLetters(int turn);

    /*
     * receives move input from player & checks validity
     */
    void getMove(int turn);

    /*
     * it's called after the player makes its move
     * updates player's pool of letters
     */
    std::vector <char> updatePlayers_letters(std::vector <char> player_letters, int turn, int move_number);

    /*
     * prints players' letters & scores
     */
    void printLettersScores();

    /*
     * prints player's name in its color
     */
    void printPlayerName(int turn);

    /*
     * calculates how many words were complete in the current turn and adds it to current player's score
     */
    void addPointsToPlayer(int word_number, std::vector <Word > word_vec, int turn, int line, int col);

    /*
     * it's called when all words are complete
     * prints players' scores (sorted)
     * announces the winner(s)
     */
    void endGame();

public:
    // constructors
    Game();
    Game(Pool pool, Board* board);

    // functions

    /*
     * informs user of how many players can play with the chosen board
     * offers chance to end the game
     * receives number of players and their names as inputs
     * assigns each player different a color
     */
    bool addPlayers();

    /*
     * main game loop
     * has 3 types of turn:
     *   1. first move & no letters available & pool not empty
     *   2. no letters available & (second move OR (first move & empty pool))
     *   3. first & second moves; letters available
     *
     * sets flag_end_of_game to true is complete_words = num_words and breaks while
     */
    void play();

};


#endif //SCRABBLE_JR_GAME_H
