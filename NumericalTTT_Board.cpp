#include "BoardGame_Classes.h"
#include "NumericalTTT_Board.h"

NumericalTTT_Board::NumericalTTT_Board() : Board<int>(3, 3) {
    board.resize(3, std::vector<int>(3, 0));
    winType = 0;
    winIndex = -1;
}

void NumericalTTT_Board::display_board() {
    std::cout << "\n-------------------\n";
    std::cout << "  0 | 1 | 2\n";
    std::cout << "-------------------\n";
    for (int r = 0; r < 3; ++r) {
        std::cout << r << " |";
        for (int c = 0; c < 3; ++c) {
            std::cout << " " << (board[r][c] == 0 ? " " : std::to_string(board[r][c])) << " |";
        }
        std::cout << "\n-------------------\n";
    }
}

bool NumericalTTT_Board::update_board(Move<int>* move) {
   int row = move->get_x();
   int col = move->get_y();
    int value = move->get_symbol();

    if (row < 0 || row >= 3 || col < 0 || col >= 3) {
        std::cout << "Invalid position (" << row << ", " << col << ").\n";
        return false;
    }
    if (board[row][col] != 0) {
        std::cout << "Cell already occupied at (" << row << ", " << col << ").\n";
        return false;
    }
    board[row][col] = value;
    return true;
}

bool NumericalTTT_Board::is_win(Player<int>* player) {
    bool isOddPlayer = (player->get_symbol() % 2 != 0); // لو لاعب فردي
    for (int r = 0; r < 3; ++r) {
        int sum = 0, sameType = 0;
        for (int c = 0; c < 3; ++c) {
            int val = board[r][c];
            sum += val;
            if (val != 0 && ((val % 2 != 0) == isOddPlayer))
                sameType++;
        }
        if (sum == 15 && sameType == 3) {
            winType = 1;
            winIndex = r;
            return true;
        };
    }

    for (int c = 0; c < 3; ++c) {
        int sum = 0, sameType = 0;
        for (int r = 0; r < 3; ++r) {
            int val = board[r][c];
            sum += val;
            if (val != 0 && ((val % 2 != 0) == isOddPlayer))
                sameType++;
        }
        if (sum == 15 && sameType == 3) {
            winType = 2;
            winIndex = c;
            return true;
        };
    }


    int diag1Sum = 0, diag1Same = 0;
    int diag2Sum = 0, diag2Same = 0;
    for (int i = 0; i < 3; ++i) {
        int v1 = board[i][i];
        int v2 = board[i][2 - i];
        diag1Sum += v1;
        diag2Sum += v2;
        if (v1 != 0 && ((v1 % 2 != 0) == isOddPlayer)) diag1Same++;
        if (v2 != 0 && ((v2 % 2 != 0) == isOddPlayer)) diag2Same++;
    }
    if (diag1Sum == 15 && diag1Same == 3) {
        winType = 3;
        winIndex = -1;
        return true;
    }

    if (diag2Sum == 15 && diag2Same == 3) {
        winType = 4;
        winIndex = -1;
        return true;
    }


    return false;
}

bool NumericalTTT_Board::is_draw(Player<int>* player) {
    if (is_win(player))return false;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[r][c] == 0) return false;
        }
    }
    return true;
};
bool NumericalTTT_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}
bool NumericalTTT_Board::is_lose(Player<int> *player) {
    bool isOddPlayer = (player->get_symbol() % 2 != 0);


    Player<int> opponent(
        isOddPlayer ? "Even Player" : "Odd Player",
        isOddPlayer ? 2 : 1,
        PlayerType::HUMAN
    );


    return is_win(&opponent);
}
void NumericalTTT_Board::highlight_winning_line() {
    std::cout << "\n-------------------\n";
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            bool highlight = false;

            if ((winType == 1 && r == winIndex) ||
                (winType == 2 && c == winIndex) ||
                (winType == 3 && r == c) ||
                (winType == 4 && r + c == 2))
                    highlight = true;

            if (highlight)
                std::cout << "(" << board[r][c] << ")";
            else
                std::cout << " " << board[r][c] << " ";

            std::cout << " |";
        }
        std::cout << "\n-------------------\n";
    }
}


NumericalTTT_Board::~NumericalTTT_Board() {}


