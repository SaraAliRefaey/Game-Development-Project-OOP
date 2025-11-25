#include <iostream>
#include <string>
#include <vector>
#include <limits> // Needed for numeric_limits in robust input
#include "BoardGame_Classes.h"
#include "NumericalTTT_Board.h"
#include "NumericalTTT_Move.h"
#include "NumericalTTT_Player.h"
#include "TTT_5X5_Classes.h"
#include "Word_TTT_Classes.h"
#include "ObstacleTTT_Board.h" // Your new board class

using namespace std;

// Function to run Numerical Tic Tac Toe (kept for reference)
void run_numerical_ttt() {

    NumericalTTT_Board board;

    // Note: Assuming NumericalTTT_Player and Move are defined in your existing files
    NumericalTTT_Player player1(1, true);
    NumericalTTT_Player player2(2, true);

    Move<int> move(0, 0, 0);
    cout <<"Welcome to Numerical Tic Tac Toe! " << endl;
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

// Game 2 : 5x5 Tic Tac Toe
void run_5x5_ttt() {
    // Note: This relies on your existing TTT_5X5_Classes.h/cpp files
    TicTacToe5x5_Board* board = new TicTacToe5x5_Board();
    TicTacToe5x5_UI* ui = new TicTacToe5x5_UI();

    Player<char>** players = ui->setup_players();

    GameManager<char> manager(board, players, ui);
    manager.run();

    delete board;
    delete ui;
    delete[] players;
}

// Game 3 : Word Tic Tac
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

void run_obstacle_ttt() {

    ObstacleTTT_Board board;


    Player<char> player1("Player X", 'X', PlayerType::HUMAN);
    Player<char> player2("Player O", 'O', PlayerType::HUMAN);

    Player<char>* players[] = {&player1, &player2};
    int turn = 0;

    cout << "Welcome to 6x6 Obstacles Tic Tac Toe! Get 3-in-a-row to win.\n";
    cout << "6 Obstacles ('#') are placed randomly and cannot be used.\n";
    board.display_board();

    Move<char> move(0, 0, ' ');

    while (true) {
        Player<char>* currentPlayer = players[turn];
        int x = -1, y = -1;
        bool valid_move = false;


        while (!valid_move) {
            cout << "\n" << currentPlayer->get_name() << " (" << currentPlayer->get_symbol() << ") Turn. Enter your move (row and column): ";

            if (!(cin >> x >> y)) {
                cout << "Invalid input format. Please enter two numbers (row and column).\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            move = Move<char>(x, y, currentPlayer->get_symbol());
            valid_move = board.update_board(&move);
        }

        board.display_board();

        if (board.is_win(currentPlayer)) {
            cout << "\n*** " << currentPlayer->get_name() << " wins! ***" << endl;
            return;
        }

        if (board.is_draw(currentPlayer)) {
            cout << "\n*** It's a draw! ***" << endl;
            return;
        }

        turn = 1 - turn;
    }
}


int main() {
    int choice ;

    do {

        cout << "  Welcome to the Board Games Collection (OOP Project) " <<endl;
        cout << "=======================================================" << endl;
        cout << "1. Play Numerical Tic Tac Toe (Group Game)" << endl;
        cout << "2. Play 5x5 Tic Tac Toe (Sara Game 3)" << endl;
        cout << "3. Play Word Tic Tac Toe (Sara Game 4 )" << endl;
        cout << "4. PLay Obstacles Tic-Tac-Toe (Group Game 10)" << endl; // Updated menu
        cout << "5. Exit" << endl;
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
        case 4: // New case to run the Obstacles game
            run_obstacle_ttt();
            break;
        case 5:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

        // This cin.ignore and cin.fail() check helps clear the buffer for next input.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (choice != 5);

    return 0;
}