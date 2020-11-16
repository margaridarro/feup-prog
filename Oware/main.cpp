#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#define MAGENTA 5
#define YELLOW 14
#define WHITE 15
using namespace std;

int board[12];
int s2, s1; //s2 = p2/computer score; s1 = p1 score

/*
 * defines the board colors
 */
void setColor(unsigned int color){
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}

/*
 * sets all houses to 4 seeds and scores to 0
 */
void resetBoard() {
    for (int i = 0; i < 12; i++)
        board[i] = 4;
    s1 = 0;
    s2 = 0;
}

/*
 * clears the screen
 */
void clear() {
    cout << flush;
    system("CLS");
}

/*
 * prints the board and calls setColor()
 */
void printBoard() {
    cout << "\n\t";
    for (int i = 12; i > 6; i--) //print p1 house numbers
        cout << i << "\t";
    cout << "\n\t-----------------------------------------\n";
    setColor(MAGENTA);
    for (int i = 11; i > 5; i--)
        cout << "\t" << board[i]; //print p2 number of seeds
    cout << "\nP2 " << s2;
    setColor(WHITE);
    if (s2 < 10) {
        cout << "|-------|-------|-------|-------|-------|-------|";
        setColor(YELLOW);
        cout << s1 << " P1\n"; //print scores
    }else{
        cout << "|------|-------|-------|-------|-------|------|";
        setColor(YELLOW);
        cout << s1 << " P1\n";
    }
    for (int i = 0; i < 6; i++)
        cout << "\t" << board[i]; //print p1 number of seeds
    setColor(WHITE);
    cout << "\n\t-----------------------------------------\n\t";
    for (int i = 1; i < 7; i++) // print p2 house numbers
        cout << i << "\t";
}

/*
 * if the move would empty all of the opponent's houses this function is called and the seeds aren't captured
 */
void resetCapture(int house, int moving_seeds1){
    int h = house;
    int final_house; // last house to get seeds
    while (true) { // moving seeds
        if (board[h % 12] != 12) {
            board[h % 12]++;
            final_house = h % 12;
            moving_seeds1--;
        }
        if (moving_seeds1 == 0)
            break;
        h++;
    }
    board[house - 1] = 0;
}

/*
 * makes copies: board, scores
 * moves the seeds using the copies
 * checks captures using the copies
 * if the capture is illegal calls resetCapture()
 * else the changed copies update the originals
 */
int moveSeeds(int c, int mode, int house, int board_copy[12]){
    int s1_1 = s1, s2_2 = s2; //score copies
    int moving_seeds = board_copy[house - 1], moving_seeds1 = board_copy[house - 1]; //seeds that will be moved and copy
    int h = house-1; // h is the "real" house number
    int final_house = 0;
    while (true) { // moving seeds
        if (h % 12 != house-1) {
            board_copy[h % 12]++;
            final_house = h % 12;
            moving_seeds--;
        }
        if (moving_seeds == 0)
            break;
        h++;
    }
    board_copy[house - 1] = 0;
    if (c % 2 == 0) { //p1 capturing
        if (final_house < 12 && final_house > 5) { // check if the final house was a p2/computer's house
            while (true) { //check which seeds are captured
                if (board_copy[final_house] != 2 && board_copy[final_house] != 3)
                    break;
                else if (final_house > 11 | final_house < 6)
                    break;
                s1_1 += board_copy[final_house];
                board_copy[final_house] = 0;
                final_house-- ;
            }
        }
        if (board_copy[6] + board_copy[7] + board_copy[8] + board_copy[9] + board_copy[10] + board_copy[11] > 0) { //check if there is at least one seed in p2/computer's houses
            for (int i = 0; i < 12; i++)
                board[i] = board_copy[i];
            s1 = s1_1;
        } else
            resetCapture(house, moving_seeds1); //no capture is done
    } else { // p2/computer capturing
        if (final_house < 6 && final_house > -1) { // check if the final house was a p1's house
            while (true) { //check which seeds are captured
                if (board_copy[final_house] != 2 && board_copy[final_house] != 3)
                    break;
                else if (final_house > 5 | final_house < 0)
                    break;
                s2_2 += board_copy[final_house];
                board_copy[final_house] = 0;
                final_house-- ;
            }
        }
        if (board_copy[0] + board_copy[1] + board_copy[2] + board_copy[3] + board_copy[4] + board_copy[5] > 0){ // check if there is at least one seed in p1's houses
            if ((c % 2 == 0) | (c % 2 != 0 && mode == 0) | (mode == 3)) {
                for (int i = 0; i < 12; i++)
                    board[i] = board_copy[i];
                s2 = s2_2;
            }
        } else
            resetCapture(house, moving_seeds1);//no capture is done
    }
    return s2_2;
}

/*
 * called if the game ends by lack of possible moves
 */
int impossibleMove(int mode){
    if (s1 > s2) {
        if (mode == 0) cout << "\nThere's no possible move available, Player 1 wins with " << s1 << " points!";
        else cout << "\nThere's no possible move available, you win with " << s1 << " points!";
    } else if (s1 < s2) {
        if (mode == 0) cout << "\nThere's no possible move available, Player 2 wins with " << s1 << " points!";
        else cout << "\nThere's no possible move available, the computer wins with " << s2 << " points!\n";
    } else {
        if (mode == 0) cout << "\nThere's no possible move available, both players have " << s1 << " points, it's a draw!\n";
        else cout << "\nThere's no possible move available, both you and the computer have " << s1 << " points, it's a draw!\n";
    }
    return -1;
}

/*
 * decides what move the computer should make
 * calls ImpossibleMoves() if there are no moves available
 * calls moveSeeds() to test the score for each move
 * if all moves return the same score, the choice is done randomly
 * else chooses one of the moves that returns the highest score
 * returns the chosen house
 */
int pcMove(int c, int mode){
    int board_copy[12], score_test[6], houses[6];
    int house = 11, gain = 0, count = 0;
    cout << "\n\nThe computer is making its move...\n";
    _sleep(1500);
    if (board[0] + board[1] + board[2] + board[3] + board[4] + board[5] == 0) {
        if (board[6] < 6 && board[7] < 5 && board[8] < 4 && board[9] < 3 && board[10] < 2 && board[11] < 1) { //there's no move available
            s2 += board[6] + board[7] + board[8] + board[9] + board[10] + board[11];
            return impossibleMove(mode);
        } else { //
            while (board[house - 1] <= 12 - house) { //i = house - 1
                for (int i = 6; i < 12; i++)
                    if (board[i] > 11 - i) //last house is chosen
                        house = i + 1;
            }
            return house;
        }
    }

    for (int k = 0; k < 6; k++) { //make a board copy to check what score would the value chosen get
        for (int i = 0; i < 12; i++)
            board_copy[i] = board[i];
        if (board[k + 6] != 0)
            score_test[k] = moveSeeds(c, mode, k + 7, board_copy);
        else
            score_test[k] = s2;
    }

    if (score_test[0] == score_test[1] && score_test[1] == score_test[2] && score_test[2] == score_test[3]
    && score_test[3] == score_test[4] && score_test[4] == score_test[5]){ // choose a random house if scores are the same
        int possible_moves[9] = {7, 8, 9, 10, 10, 11, 11, 12, 12}; //last 3 houses are more likely to be chosen
        do {
            int rand_index = rand() % 9;
            house = possible_moves[rand_index];
        } while (board[house-1] == 0);
    } else { //choose the move with the highest score
        for (int k = 0; k < 6; k++){
            if (score_test[k] > gain){
                gain = score_test[k];
                houses[0] = k + 7; houses[1] = 0; houses[2] = 0;houses[3] = 0;houses[4] = 0;houses[5] = 0;
                count = 1;
            } else if (score_test[k] == gain && board[k+6] != 0) {
                //house = k + 7;
                houses[count] = k + 7; // k + 7 = house
                if (score_test[k] > 1)
                    count++;
            }
        }
        if (count > 1) {
            int rand_index = rand() % count;
            house = houses[rand_index];
        } else
            house = houses[0];
    }
    return house;
}

/*
 * checks if the move inserted by player 1 is legal
 * returns house
 */
int p1Move(int mode){
    int house;
    cout << "\n\n";
    if (mode == 0)
        cout << "Player 1:";
    cout << "\nChoose the seeds you wish to move (1-6).\n";
    cin >> house; cin.clear(); cin.ignore(INT_MAX, '\n');
    if (house == -1) return house;
    while (house > 6 | house < 1) {
        cout << "Impossible move, choose a house between 1 and 6.\n"; //exclude p2 houses
        cin >> house; cin.clear(); cin.ignore(INT_MAX, '\n');
        if (house == -1) return house;
    }
    while (board[house - 1] == 0) {
        cout << "Choose a house that's not empty.\n"; //exclude p1 empty houses
        cin >> house; cin.clear(); cin.ignore(INT_MAX, '\n');
        if (house == -1) return house;
    }
    if (board[6] + board[7] + board[8] + board[9] + board[10] + board[11] == 0) { //check if there's any move available
        while (board[house-1] <= 6 - house) {
            if (board[0] < 6 && board[1] < 5 && board[2] < 4 && board[3] < 3 && board[4] < 2 && board[5] < 1) {
                s1 += board[0] + board[1] + board[2] + board[3] + board[4] + board[5];
                return impossibleMove(mode);
            } else { // there's no move available
                cout << "Impossible move, make a move that allows your opponent to have seeds on their side\n";
                cin >> house; cin.clear(); cin.ignore(INT_MAX, '\n');
            }
        }
    }
    return house;
}

/*
 * checks if the move inserted by player 1 is possible
 * returns house
 */
int p2Move(int mode){
    int house;
    cout << "\n\nPlayer 2:\nChoose the seeds you wish to move (7-12)\n";
    cin >> house; cin.clear(); cin.ignore(INT_MAX, '\n');
    if (house == -1) return house;
    while (house < 7 | house > 12) {
        cout << "Impossible move, choose a house between 7 and 12\n"; //exclude p1 houses
        cin >> house; cin.clear(); cin.ignore(INT_MAX, '\n');
        if (house == -1) return house;
    }
    while (board[house - 1] == 0) {
        cout << "Choose a house that's not empty\n"; //exclude p2 empty houses
        cin >> house; cin.clear(); cin.ignore(INT_MAX, '\n');
        if (house == -1) return house;
    }
    if (board[0] + board[1] + board[2] + board[3] + board[4] + board[5] == 0) { //check if there's any move available
        if (board[6] < 6 && board[7] < 5 && board[8] < 4 && board[9] < 3 && board[10] < 2 && board[11] < 1) {
            s2 += board[6] + board[7] + board[8] + board[9] + board[10] + board[11];
            return impossibleMove(mode);
        } else { // there's no move available
            while (board[house - 1] <= 12 - house) {
                cout << "Impossible move, make a move that allows your opponent to have seeds on their side\n";
                cin >> house; cin.clear();cin.ignore(INT_MAX, '\n');
            }
        }
    }
    return house;
}

/*
 * prints the final score of the winner and asks the players if they want to play again
 * returns the players' answer
 */
char endPlay(int house){
    char response;
    if (s1 >= 25) {
        cout << "\nYou win with " << s1 << " points!";
    } else if (s2 >= 25) {
        cout << "\nComputer wins with " << s2 << " points...";
    } else if (s1 == 24 && s2 == 24) {
        cout << "\nIt's a draw, both you and the computer have 24 points.";
    }
    if (house == -1) {
        clear();
        cout << "\nYou have chosen to end this game.";
        _sleep(1000);
    }
    cout << "\nIf you wish to start a new play in multiplayer mode, press 'm'.\nIf you wish to start a new play in singleplayer mode, press 's'.\nIf you wish to stop playing press 'e'.\n";
    cin >> response;
    clear();
    return (response);
}

/*
 * defines whose turn it is (using int c)
 * calls checkMove()
 * if checkMove() returns -1 it means there are no possible moves
 * calls moveSeeds(), clear(), printBoard() and endPlay() if the scores indicate the end
 */
char play(int mode){
    int c = 0;
    int house, board_copy[12];
    int mode_copy = mode;
    while (true) {
        if (c % 2 == 0) house = p1Move(mode);
        else if (mode == 0) house = p2Move(mode);
        else{
            house = pcMove(c, mode);
            mode_copy = 3;
        }
        if (house == -1) // no move available, restart game
            return endPlay(house);

        for (int i = 0; i < 12; i++) //make a board copy to check if the move is valid
            board_copy[i] = board[i];

        moveSeeds(c, mode_copy, house, board_copy);
        mode_copy = mode;
        clear();
        printBoard();
        c++;
        if (s1 >= 25 | s2 >= 25 | (s1 == 24 && s2 == 24))
            return endPlay(house);
    }
}

/*
 * decides which type of game will be played
 * ends the game if instructed to
 * calls resetBoard(), printBoard() and play()
 */
int main() {
    srand(time(NULL));
    char letter;
    cout << "\nWelcome to Margarida's Oware Game!\n Type 'm' to play in multiplayer mode or 's' to play in singleplayer mode.\n If you'd like to exit the game press 'e'.\n During the game, if you'd like to end your play, enter -1 instead of choosing a house number.\n";
    cin >> letter;
    clear();
    int mode;
    while(true){
        if (letter == 'm' | letter == 'M') {
            cout << "\nYou have chosen to play in multiplayer mode, may the best player win!\n";
            resetBoard();
            printBoard();
            mode = 0; //multiplayer mode
            letter = play(mode);
        } else if (letter == 's' | letter == 'S') {
            cout << "\nYou have chosen to play in singleplayer mode, good luck!\n";
            resetBoard();
            printBoard();
            mode = 1; //singleplayer mode
            letter = play(mode);
        } else if (letter == 'e' | letter == 'E'){
            cout << "The game has ended, hope to see you again soon.";
            _sleep(2000);
            break;
        } else{
            cout << "\nYour input is invalid.\n\nIf you wish to start a new play in multiplayer mode, press 'm'.\nIf you wish to start a new play in singleplayer mode, press 's'.\nIf you wish to stop playing press 'e'.\n";
            cin >> letter;
            clear();
        }
    }
    return 0;
}