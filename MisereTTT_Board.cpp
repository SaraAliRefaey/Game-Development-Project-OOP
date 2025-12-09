#include "MisereTTT_Board.h"
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;


MisereTTT_Board::MisereTTT_Board() : Board<char>(3, 3) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
    }
}


void MisereTTT_Board::display_board() {
    cout << "\n-------------------\n";
    for (int i : {0, 1, 2}) {
        cout << "|";
        for (int j : {0, 1, 2}) {
            cout << " " << board[i][j] << " |";
        }
        cout << "\n-------------------\n";
    }
}


bool MisereTTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != ' ') {
        return false;
    }
    board[x][y] = symbol;
    n_moves++;
    return true;
}

// Win Check
bool MisereTTT_Board::check_3_in_row(char symbol) const {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
            (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)) return true;
    }
    // Check diagonals
    if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) return true;
    return false;
}

// is_win
bool MisereTTT_Board::is_win(Player<char>* player) {
    return check_3_in_row(player->get_symbol());
}

bool MisereTTT_Board::is_lose(Player<char>* player) {
    return false;
}


// is_draw
bool MisereTTT_Board::is_draw(Player<char>* player) {
    return n_moves == 9 && !check_3_in_row('X') && !check_3_in_row('O');
}

// game_is_over
bool MisereTTT_Board::game_is_over(Player<char>* player) {
    return n_moves == 9 || check_3_in_row('X') || check_3_in_row('O');
}



int MisereTTT_Board::minimax(MisereTTT_Board current_board, int depth, char maximizing_player, char current_player) {
    char opponent_player = get_opponent_symbol(current_player);

    // Terminal state checks
    if (current_board.check_3_in_row(maximizing_player)) {
        return (-10 + depth);
    }
    if (current_board.check_3_in_row(get_opponent_symbol(maximizing_player))) {
        return (10 - depth);
    }
    if (current_board.n_moves == 9) {
        return 0;
    }

    int bestScore = (current_player == maximizing_player) ? numeric_limits<int>::min() : numeric_limits<int>::max();

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (current_board.board[i][j] == ' ') {
                current_board.board[i][j] = current_player;
                current_board.n_moves++;

                int score = minimax(current_board, depth + 1, maximizing_player, opponent_player);

                current_board.board[i][j] = ' ';
                current_board.n_moves--;

                if (current_player == maximizing_player) {
                    bestScore = max(bestScore, score);
                } else {
                    bestScore = min(bestScore, score);
                }
            }
        }
    }
    return bestScore;
}


pair<int, int> MisereTTT_Board::get_computer_move(char symbol) {
    int bestMoveRow = -1;
    int bestMoveCol = -1;
    int bestScore = numeric_limits<int>::min();

    cout << "\n--- AI (" << symbol << ") is calculating move... ---\n";

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                MisereTTT_Board next_board = *this;
                next_board.board[i][j] = symbol;
                next_board.n_moves++;

                if (next_board.check_3_in_row(symbol)) {
                    int score = numeric_limits<int>::min() + 1;
                    if (bestMoveRow == -1 || score > bestScore) {
                        bestMoveRow = i;
                        bestMoveCol = j;
                        bestScore = score;
                    }
                } else {
                    char opponent_symbol = get_opponent_symbol(symbol);
                    int score = minimax(next_board, 0, symbol, opponent_symbol);

                    if (score > bestScore) {
                        bestScore = score;
                        bestMoveRow = i;
                        bestMoveCol = j;
                    }
                }
            }
        }
    }

    if (bestMoveRow == -1) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    return {i, j};
                }
            }
        }
    }

    return {bestMoveRow, bestMoveCol};
}