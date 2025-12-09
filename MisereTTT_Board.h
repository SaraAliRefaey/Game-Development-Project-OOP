#ifndef MISERETTT_BOARD_H
#define MISERETTT_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include <utility>

inline char get_opponent_symbol(char symbol) {
    return (symbol == 'X' ? 'O' : 'X');
}

class MisereTTT_Board : public Board<char> {
private:
    char board[3][3];
    int minimax(MisereTTT_Board current_board, int depth, char maximizing_player, char current_player);
    bool check_3_in_row(char symbol) const;

public:
    MisereTTT_Board();

    std::pair<int, int> get_computer_move(char symbol);

    bool update_board(Move<char>* move) override;
    void display_board();

    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool is_lose(Player<char>* player) override;
};

#endif // MISERETTT_BOARD_H