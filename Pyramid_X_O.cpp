#include "Pyramid_X_O.h"
#include <iostream>
#include <cctype>

using namespace std;

Pyramid_X_O_Board::Pyramid_X_O_Board() : Board<char>(3, 5) {
    n_moves = 0;
}

bool Pyramid_X_O_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = toupper(move->get_symbol());

    if (x < 0 || x >= 3 || y < 0 || y >= 5 || board[x][y] != 0) {
        return false;
    }

    if (x == 0 && y != 2) return false;
    if (x == 1 && (y < 1 || y > 3)) return false;

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool Pyramid_X_O_Board::is_win(Player<char>* p) {
    char s = toupper(p->get_symbol());

    if (board[1][1] == s && board[1][2] == s && board[1][3] == s) return true;

    if (board[2][0] == s && board[2][1] == s && board[2][2] == s) return true;
    if (board[2][1] == s && board[2][2] == s && board[2][3] == s) return true;
    if (board[2][2] == s && board[2][3] == s && board[2][4] == s) return true;

    if (board[0][2] == s && board[1][2] == s && board[2][2] == s) return true;

    if (board[0][2] == s && board[1][1] == s && board[2][0] == s) return true;
    if (board[0][2] == s && board[1][3] == s && board[2][4] == s) return true;

    return false;
}

bool Pyramid_X_O_Board::is_draw(Player<char>* p) {
    return (n_moves == 9 && !is_win(p));
}

bool Pyramid_X_O_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

Pyramid_X_O_UI::Pyramid_X_O_UI() : UI<char>("Pyramid Tic-Tac-Toe", 3) {}

Player<char>* Pyramid_X_O_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Pyramid_X_O_UI::get_move(Player<char>* player) {
    int x, y;
    cout << player->get_name() << " (" << player->get_symbol() << ") select (row col): ";
    cin >> x >> y;
    return new Move<char>(x, y, player->get_symbol());
}
