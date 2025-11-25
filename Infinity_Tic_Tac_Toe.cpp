#include "Infinity_Tic_Tac_Toe.h"

#include <cctype>
#include <iostream>

using namespace std;

Infinity_Tic_Tac_Toe::Infinity_Tic_Tac_Toe() : Board<char>(3, 3) {
    n_moves = 0;
}

bool Infinity_Tic_Tac_Toe::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = toupper(move->get_symbol());

    if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != 0) {
        return false;
    }

    if (symbol == 'X') {
        if (x_moves.size() == 3) {
            Point old = x_moves[0];
            board[old.x][old.y] = 0;
            x_moves.erase(x_moves.begin());
        }
        x_moves.push_back({ x, y });
    }
    else if (symbol == 'O') {
        if (o_moves.size() == 3) {
            Point old = o_moves[0];
            board[old.x][old.y] = 0;
            o_moves.erase(o_moves.begin());
        }
        o_moves.push_back({ x, y });
    }

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool Infinity_Tic_Tac_Toe::is_win(Player<char>* p) {
    char symbol = toupper(p->get_symbol());

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
    }
    if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) {
        return true;
    }
    return false;
}

bool Infinity_Tic_Tac_Toe::is_draw(Player<char>* p) {
    return false;
}

bool Infinity_Tic_Tac_Toe::game_is_over(Player<char>* p) {
    return is_win(p);
}

Infinity_UI::Infinity_UI() : UI<char>("Infinity Tic-Tac-Toe", 3) {}

Player<char>* Infinity_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Infinity_UI::get_move(Player<char>* player) {
    int x, y;
    cout << player->get_name() << " (" << player->get_symbol() << ") select (row col): ";
    cin >> x >> y;
    return new Move<char>(x, y, player->get_symbol());
}