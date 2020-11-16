#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Board.h"
#include "Pool.h"
#include "Player.h"
#include "Game.h"
#include "common.h"

using namespace std;

int main() {
    srand(time(NULL));
    setColor(BLACK, WHITE);
    cout << WELCOME;
    setColor(WHITE, BLACK);
    char new_game;
    bool flag_end_game = false;
    while (true){
        Player winner;
        string board_name;
        cout << CHOOSING_BOARD;
        cin >> board_name;
        Board board = Board(board_name); // create object board; open board file; build board; insert words
        Pool pool = Pool(); // create object pool
        pool.addLettersToPool(board.getBrd()); // include board letters in pool vec (pl)

        while (pool.getPl().size() < 14){ // number of letters must be at least 14
            cout << BOARD_ERROR;
            cin >> board_name;
            if (board_name == "/quit") {
                flag_end_game = true;
                break;
            }
            board = Board(board_name); // create object board; open board file; build board; insert words
            pool = Pool();
            pool.addLettersToPool(board.getBrd()); // include board letters in pool vec (pl)
        }
        if (flag_end_game) break;
        Game game = Game(pool, &board); // update object game
        if (game.addPlayers()) break;  // choose number of players, create Player objects
        game.play(); // start playing the game
        do {
            cout << PLAY_AGAIN;
            cin >> new_game;
        } while (new_game != 'y' && new_game != 'Y' && new_game != 'n' && new_game != 'N');
        if (new_game == 'n' || new_game == 'N') break;
    }
}