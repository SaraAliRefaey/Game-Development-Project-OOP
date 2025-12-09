#ifndef DIAMONDT_BOARD_H
#define DIAMONDT_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class DiamondTTT_Board : public Board<char> {
private:
    static const int BOARD_SIZE = 5;
    char board[BOARD_SIZE][BOARD_SIZE];
    int minimax(DiamondTTT_Board current_board, int depth, char maximizing_player, char current_player);

    bool check_simultaneous_win(char symbol) const;

    bool check_4_in_row(char symbol) const;
    bool check_2x2_square(char symbol) const;

public:
    DiamondTTT_Board();
    std::pair<int, int> get_computer_move(char symbol);

    bool update_board(Move<char>* move) override;
    void display_board();

    bool is_lose(Player<char>* player) override;
    bool is_win(Player<char>* player) override; 
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

#endif // DIAMONDT_BOARD_H