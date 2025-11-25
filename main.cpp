#include <iostream>
#include <string>
#include <vector>
#include "BoardGame_Classes.h"
#include "NumericalTTT_Board.h"
#include "NumericalTTT_Move.h"
#include "NumericalTTT_Player.h"
#include "TTT_5X5_Classes.h" 
#include "Word_TTT_Classes.h"
#include "Infinity_Tic_Tac_Toe.h"

using namespace std;

void run_numerical_ttt() {
    NumericalTTT_Board board;

    NumericalTTT_Player player1(1, true);
    NumericalTTT_Player player2(2, true);

    Move<int> move(0, 0, 0);
    cout << "Welcome to Numerical Tic Tac Toe! " << endl;
    board.display_board();

    while (!board.game_is_over(&player1) && !board.game_is_over(&player2)) {
        cout << "\n--- Player 1 Turn (odd numbers) ---\n";
        player1.get_move(move, board);
        board.display_board();
        if (board.is_win(&player1)) {
            cout << " Player 1 wins!" << endl;
            board.highlight_winning_line();
            break;
        }
        if (board.is_draw(&player1)) {
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
}

void run_5x5_ttt() {
    TicTacToe5x5_Board* board = new TicTacToe5x5_Board();
    TicTacToe5x5_UI* ui = new TicTacToe5x5_UI();

    Player<char>** players = ui->setup_players();

    GameManager<char> manager(board, players, ui);
    manager.run();

    delete board;
    delete ui;
    delete[] players;
}

void run_word_ttt() {
    WordTicTacToe_Board* board = new WordTicTacToe_Board();
    WordTicTacToe_UI* ui = new WordTicTacToe_UI();

    Player<char>** players = ui->setup_players();

    GameManager<char> manager(board, players, ui);
    manager.run();

    delete board;
    delete ui;
    delete[] players;
}

void run_infinity_ttt() {
    Player<char>* players[2];
    players[0] = new Player<char>("Player 1", 'X', PlayerType::HUMAN);
    players[1] = new Player<char>("Player 2", 'O', PlayerType::HUMAN);

    Board<char>* board = new Infinity_Tic_Tac_Toe();
    Infinity_UI* ui = new Infinity_UI();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
}

int main() {
    int choice;

    do {
        cout << "\nWelcome to the Board Games Collection (OOP Project)\n";
        cout << "=======================================================\n";
        cout << "1. Play Numerical Tic Tac Toe\n";
        cout << "2. Play 5x5 Tic Tac Toe\n";
        cout << "3. Play Word Tic Tac Toe\n";
        cout << "4. Play Infinity Tic Tac Toe\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            run_numerical_ttt();
            break;
        case 2:
            run_5x5_ttt();
            break;
        case 3:
            run_word_ttt();
            break;
        case 4:
            run_infinity_ttt();
            break;
        case 5:
            cout << "Goodbye!...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
