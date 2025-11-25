//#pragma once
//class Infinity_Tic_Tac_Toe
//{
//};

#ifndef INFINITY_TIC_TAC_TOE_H
#define INFINITY_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <vector>

class Infinity_Tic_Tac_Toe : public Board<char> {
private:
    struct Point { int x, y; };
    vector<Point> x_moves;
    vector<Point> o_moves;

public:
    Infinity_Tic_Tac_Toe();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
    bool is_lose(Player<char>* p) override { return false; }
};

class Infinity_UI : public UI<char> {
public:
    Infinity_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif