
#include "SUS_Board.h"
#include "BoardGame_Classes.h"


SUS_Board::SUS_Board() : Board<char>(3, 3) {
    board.resize(3, std::vector<char>(3, '-'));
}

void SUS_Board::display_board() {
    std::cout << "\n-------------------\n";
    std::cout << "  0 | 1 | 2\n";
    std::cout << "-------------------\n";
    for (int r = 0; r < 3; ++r) {
        std::cout << r << " |";
        for (int c = 0; c < 3; ++c) {
            char cell = board[r][c];
            std::cout << " " << (cell == '-' ? ' ' : cell) << " |";
        }
        std::cout << "\n-------------------\n";
    }
}

bool SUS_Board::update_board(Move<char>*m)  {
    int pos = m->get_x();
    char value = m->get_symbol();

    int row = pos / 3;
    int col = pos % 3;

    if (pos < 0 || pos > 8) return false;
    if (board[row][col] != '-') return false;

    board[row][col] = value;
    return true;

}

bool SUS_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();


    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return true;

        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
            return true;
    }


    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return true;

    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return true;

    return false;
}

bool SUS_Board::is_draw(Player<char>* player) {
    if (is_win(player))return false;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[r][c] == '-') return false;
        }
    }
    return true;
};
bool SUS_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
bool SUS_Board::is_lose(Player<char> *player) {
    return is_win(player);

}

SUS_Board::~SUS_Board() {

}



