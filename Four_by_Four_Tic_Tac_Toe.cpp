#include "Four_by_Four_Tic_Tac_Toe.h"
#include <iostream>
#include <cctype>

using namespace std;

Four_by_Four_Board::Four_by_Four_Board() : Board<char>(4, 4) {
    n_moves = 0;
}

bool Four_by_Four_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = toupper(move->get_symbol());

    if (x < 0 || x >= 4 || y < 0 || y >= 4 || board[x][y] != 0) {
        return false;
    }

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool Four_by_Four_Board::is_win(Player<char>* p) {
    char s = toupper(p->get_symbol());

    for (int i = 0; i < 4; i++) {
        if ((board[i][0] == s && board[i][1] == s && board[i][2] == s) ||
            (board[i][1] == s && board[i][2] == s && board[i][3] == s)) {
            return true;
        }
    }

    for (int i = 0; i < 4; i++) {
        if ((board[0][i] == s && board[1][i] == s && board[2][i] == s) ||
            (board[1][i] == s && board[2][i] == s && board[3][i] == s)) {
            return true;
        }
    }

    if ((board[0][0] == s && board[1][1] == s && board[2][2] == s) ||
        (board[1][1] == s && board[2][2] == s && board[3][3] == s)) {
        return true;
    }

    if ((board[0][3] == s && board[1][2] == s && board[2][1] == s) ||
        (board[1][2] == s && board[2][1] == s && board[3][0] == s)) {
        return true;
    }

    if ((board[0][1] == s && board[1][2] == s && board[2][3] == s) ||
        (board[1][0] == s && board[2][1] == s && board[3][2] == s)) {
        return true;
    }

    if ((board[0][2] == s && board[1][1] == s && board[2][0] == s) ||
        (board[1][3] == s && board[2][2] == s && board[3][1] == s)) {
        return true;
    }

    return false;
}

bool Four_by_Four_Board::is_draw(Player<char>* p) {
    return (n_moves == 16 && !is_win(p));
}

bool Four_by_Four_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

Four_by_Four_UI::Four_by_Four_UI() : UI<char>("4x4 Tic-Tac-Toe (Win with 3 in a row)", 4) {}

Player<char>* Four_by_Four_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Four_by_Four_UI::get_move(Player<char>* player) {
    int x, y;
    cout << player->get_name() << " (" << player->get_symbol() << ") select (row col): ";
    cin >> x >> y;
    return new Move<char>(x, y, player->get_symbol());
}
