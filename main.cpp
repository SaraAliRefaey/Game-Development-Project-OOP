#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <utility> // For std::pair
#include "BoardGame_Classes.h"
// Include your existing files
#include "NumericalTTT_Board.h"
#include "NumericalTTT_Move.h"
#include "NumericalTTT_Player.h"
#include "TTT_5X5_Classes.h"
#include "Word_TTT_Classes.h"
#include "ObstacleTTT_Board.h"
// Include new files
#include "MisereTTT_Board.h"
#include "DiamondTTT_Board.h"

using namespace std;

class TTT_Player : public Player<char> {
public:
    TTT_Player(string name, char symbol) : Player<char>(name, symbol, PlayerType::HUMAN) {}


    void get_move(Move<char>& m, Board<char>& b) {
        int x, y;
        cout << "\n--- Player " << get_name() << " (" << get_symbol() << ") Turn ---\n";

        int max_dim = 5;

        cout << "Enter row and column (0-" << max_dim - 1 << " 0-" << max_dim - 1 << ") separated by space: ";

        while (!(cin >> x >> y) || x < 0 || x >= max_dim || y < 0 || y >= max_dim) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid coordinate or input. Please enter valid row and column: ";
        }

        m = Move<char>(x, y, get_symbol());
    }
};

void safe_display_board(Board<char>* board) {
    if (DiamondTTT_Board* diamond_board = dynamic_cast<DiamondTTT_Board*>(board)) {
        diamond_board->display_board();
    } else if (MisereTTT_Board* misere_board = dynamic_cast<MisereTTT_Board*>(board)) {
        misere_board->display_board();
    } else {
        cout << "Error: Cannot display board type safely." << endl;
    }
}



void run_ttt_game(Board<char>* board, const string& game_name) {
    int p1_type, p2_type;

    cout << "\n--- " << game_name << " Setup ---\n";
    cout << "Player 1 (X) - 1 for Human, 2 for Computer: ";
    if (!(cin >> p1_type)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); p1_type = 1; }
    cout << "Player 2 (O) - 1 for Human, 2 for Computer: ";
    if (!(cin >> p2_type)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); p2_type = 1; }

    Player<char>* player1 = new TTT_Player("Player 1", 'X');
    Player<char>* player2 = new TTT_Player("Player 2", 'O');

    Player<char>* players[] = {player1, player2};
    int player_types[] = {p1_type, p2_type};
    int turn = 0;

    cout << "\nWelcome to " << game_name << "!\n";
    safe_display_board(board); // <-- Use safe helper

    while (!board->game_is_over(players[turn])) {
        Player<char>* current_player = players[turn];
        Player<char>* opponent_player = players[1 - turn];
        Move<char> move(0, 0, current_player->get_symbol());
        pair<int, int> best_pos = {-1, -1};

        bool move_success = false;

        if (player_types[turn] == 1) {
            TTT_Player* ttt_player = dynamic_cast<TTT_Player*>(current_player);
            if (!ttt_player) {
                cout << "Error: Player type mismatch in game loop." << endl;
                break;
            }

            while (!move_success) {
                ttt_player->get_move(move, *board);
                if (board->update_board(&move)) {
                    move_success = true;
                } else {
                    cout << "Invalid move (Cell occupied or out of bounds). Please try again." << endl;
                }
            }
        } else {
            if (MisereTTT_Board* misere_board = dynamic_cast<MisereTTT_Board*>(board)) {
                best_pos = misere_board->get_computer_move(current_player->get_symbol());
            } else if (DiamondTTT_Board* diamond_board = dynamic_cast<DiamondTTT_Board*>(board)) {
                best_pos = diamond_board->get_computer_move(current_player->get_symbol());
            } else {
                 cout << "Error: AI not implemented for this board type." << endl;
                 break;
            }

            move = Move<char>(best_pos.first, best_pos.second, current_player->get_symbol());
            cout << "AI played at (" << best_pos.first << ", " << best_pos.second << ")\n";
            board->update_board(&move);
        }

        safe_display_board(board);

        if (MisereTTT_Board* misere_board = dynamic_cast<MisereTTT_Board*>(board)) {
            if (misere_board->is_win(current_player)) {
                cout << "\n*** " << current_player->get_name() << " (" << current_player->get_symbol()
                     << ") completed a line and **LOSES**! ***" << endl;
                cout << "\n*** " << opponent_player->get_name() << " (" << opponent_player->get_symbol()
                     << ") **WINS**! ***" << endl;
                break;
            }
        }


        if (board->is_win(current_player)) {
            cout << "\n*** " << current_player->get_name() << " (" << current_player->get_symbol()
                 << ") **WINS**! ***" << endl;
            break;
        }


        if (board->is_draw(current_player)) {
            cout << "\n*** It's a draw! ***" << endl;
            break;
        }

        turn = 1 - turn;
    }

    delete player1;
    delete player2;
    delete board;
}

void run_misere_ttt() {
    run_ttt_game(new MisereTTT_Board(), "Misère Tic Tac Toe (3x3, Player who makes 3-in-a-row LOSES)");
}

void run_diamond_ttt() {
    run_ttt_game(new DiamondTTT_Board(), "Diamond Tic-Tac-Toe (5x5, 4-in-a-Row or 2x2 Square WINS)");
}

int main() {
    int choice;

    do {
        cout << "\n  Welcome to the Board Games Collection (OOP Project) " << endl;
        cout << "=======================================================" << endl;
        cout << "1. Play Numerical Tic Tac Toe (Group Game)" << endl;
        cout << "2. Play 5x5 Tic Tac Toe (Sara Game 3)" << endl;
        cout << "3. Play Word Tic Tac Toe (Sara Game 4 )" << endl;
        cout << "4. PLay Obstacles Tic-Tac-Toe (Group Game 10)" << endl;
        cout << "5. Play Misère Tic Tac Toe" << endl;
        cout << "6. Play Diamond Tic-Tac-Toe" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        switch (choice) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: run_misere_ttt(); break;
            case 6: run_diamond_ttt(); break;
            case 7: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (choice != 7);
    return 0;
}