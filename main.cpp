#include <iostream>
#include"NumericalTTT_Board.h"
#include "BoardGame_Classes.h"
#include "NumericalTTT_Move.h"
#include "NumericalTTT_Player.h"


using namespace std;
int main() {
    NumericalTTT_Board board;
    NumericalTTT_Player player1(1,true);
    NumericalTTT_Player player2(2,true);
    Move<int>move(0,0,0);
    cout << "Welcome to Numerical Tic Tac Toe! " << endl;
    board.display_board();

    while (!board.game_is_over(&player1) && !board.game_is_over(&player2) ) {
        cout << "\n--- Player 1 Turn (odd numbers) ---\n";
        player1.get_move(move, board);
        board.display_board();
        if (board.is_win(&player1) ) {
            cout << " Player 1 wins!" << endl;
            board.highlight_winning_line();


            break;
        }
        if (board.is_draw(&player1) ) {
            cout << " It's a draw!" << endl;
            break;
        }

        cout << "\n--- Player 2 Turn (even numbers) ---\n";
        player2.get_move(move, board);
        board.display_board();
        if (board.is_win(&player2)) {
            cout << " Player 2 wins!" << endl;
            board.highlight_winning_line();
            break;
        }
        if (board.is_draw(&player2)) {
            cout << " It's a draw!" << endl;
            break;
        }
    }

    return 0;
}


