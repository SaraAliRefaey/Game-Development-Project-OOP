#include "DiamondTTT_Board.h"
#include "MisereTTT_Board.h"
#include <limits>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int MAX_DEPTH = 3;
const int BOARD_SIZE = 5;


DiamondTTT_Board::DiamondTTT_Board() : Board<char>(BOARD_SIZE, BOARD_SIZE) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = ' ';
    }
}

void DiamondTTT_Board::display_board() {
    cout << "\n-----------------------------------------\n";
    for (int i : {0, 1, 2, 3, 4}) {
        cout << "|";
        for (int j : {0, 1, 2, 3, 4}) {
            cout << " " << board[i][j] << " |";
        }
        cout << "\n-----------------------------------------\n";
    }
}

bool DiamondTTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[x][y] != ' ') {
        return false;
    }
    board[x][y] = symbol;
    n_moves++;
    return true;
}


std::vector<std::vector<std::pair<int, int>>> find_lines(char symbol, int length, const char board[BOARD_SIZE][BOARD_SIZE]) {
    std::vector<std::vector<std::pair<int, int>>> found_lines;
    const int N = BOARD_SIZE;


    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N - length; j++) {
            bool line_found = true;
            std::vector<std::pair<int, int>> current_line;
            for (int k = 0; k < length; k++) {
                if (board[i][j + k] != symbol) { line_found = false; break; }
                current_line.push_back({i, j + k});
            }
            if (line_found) found_lines.push_back(current_line);
        }
    }


    for (int j = 0; j < N; j++) {
        for (int i = 0; i <= N - length; i++) {
            bool line_found = true;
            std::vector<std::pair<int, int>> current_line;
            for (int k = 0; k < length; k++) {
                if (board[i + k][j] != symbol) { line_found = false; break; }
                current_line.push_back({i + k, j});
            }
            if (line_found) found_lines.push_back(current_line);
        }
    }


    for (int i = 0; i <= N - length; i++) {
        for (int j = 0; j <= N - length; j++) {
            bool line_found = true;
            std::vector<std::pair<int, int>> current_line;
            for (int k = 0; k < length; k++) {
                if (board[i + k][j + k] != symbol) { line_found = false; break; }
                current_line.push_back({i + k, j + k});
            }
            if (line_found) found_lines.push_back(current_line);
        }
    }

    // 4. Anti-Diagonal Lines (Top-Right to Bottom-Left)
    for (int i = 0; i <= N - length; i++) {
        for (int j = length - 1; j < N; j++) {
            bool line_found = true;
            std::vector<std::pair<int, int>> current_line;
            for (int k = 0; k < length; k++) {
                if (board[i + k][j - k] != symbol) { line_found = false; break; }
                current_line.push_back({i + k, j - k});
            }
            if (line_found) found_lines.push_back(current_line);
        }
    }
    return found_lines;
}



bool DiamondTTT_Board::check_simultaneous_win(char symbol) const {
    std::vector<std::vector<std::pair<int, int>>> lines_of_3 = find_lines(symbol, 3, board);
    std::vector<std::vector<std::pair<int, int>>> lines_of_4 = find_lines(symbol, 4, board);

    if (lines_of_3.empty() || lines_of_4.empty()) {
        return false;
    }


    for (const auto& line_3 : lines_of_3) {
        for (const auto& line_4 : lines_of_4) {

            int common_marks = 0;

            for (const auto& p3 : line_3) {
                for (const auto& p4 : line_4) {
                    if (p3.first == p4.first && p3.second == p4.second) { // Coordinates match
                        common_marks++;
                    }
                }
            }

            if (common_marks >= 1) {
                return true;
            }
        }
    }
    return false;
}

bool DiamondTTT_Board::check_4_in_row(char symbol) const { return false; }
bool DiamondTTT_Board::check_2x2_square(char symbol) const { return false; }



bool DiamondTTT_Board::is_win(Player<char>* player) {
    return check_simultaneous_win(player->get_symbol());
}

bool DiamondTTT_Board::is_lose(Player<char>* player) {
    char opponent_symbol = get_opponent_symbol(player->get_symbol());
    Player<char> opponent("Opponent", opponent_symbol, PlayerType::HUMAN);
    return is_win(&opponent);
}

bool DiamondTTT_Board::is_draw(Player<char>* player) {
    if (n_moves < BOARD_SIZE * BOARD_SIZE) return false;
    return !check_simultaneous_win('X') && !check_simultaneous_win('O');
}

bool DiamondTTT_Board::game_is_over(Player<char>* player) {
    return n_moves == BOARD_SIZE * BOARD_SIZE || is_win(player) || is_lose(player);
}


int DiamondTTT_Board::minimax(DiamondTTT_Board current_board, int depth, char maximizing_player, char current_player) {
    char minimizing_player = get_opponent_symbol(maximizing_player);

    if (current_board.check_simultaneous_win(maximizing_player)) return 100 - depth;
    if (current_board.check_simultaneous_win(minimizing_player)) return -100 + depth;

    if (current_board.n_moves == BOARD_SIZE * BOARD_SIZE || depth >= MAX_DEPTH) return 0;

    char opponent_player = get_opponent_symbol(current_player);
    int bestScore = (current_player == maximizing_player) ? numeric_limits<int>::min() : numeric_limits<int>::max();

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (current_board.board[i][j] == ' ') {
                current_board.board[i][j] = current_player;
                current_board.n_moves++;

                int score = minimax(current_board, depth + 1, maximizing_player, opponent_player);

                current_board.board[i][j] = ' ';
                current_board.n_moves--;

                if (current_player == maximizing_player) bestScore = max(bestScore, score);
                else bestScore = min(bestScore, score);
            }
        }
    }
    return bestScore;
}


pair<int, int> DiamondTTT_Board::get_computer_move(char symbol) {
    int bestMoveRow = -1;
    int bestMoveCol = -1;
    int bestScore = numeric_limits<int>::min();

    cout << "\n--- AI (" << symbol << ") is calculating move... (Warning: 5x5 Minimax is slow; search depth is limited to " << MAX_DEPTH << ") ---\n";

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == ' ') {
                DiamondTTT_Board next_board = *this;
                next_board.board[i][j] = symbol;
                next_board.n_moves++;

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

    if (bestMoveRow == -1) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == ' ') return {i, j};
            }
        }
    }

    return {bestMoveRow, bestMoveCol};
}