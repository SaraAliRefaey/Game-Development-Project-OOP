#ifndef PYRAMID_X_O_H
#define PYRAMID_X_O_H

#include "BoardGame_Classes.h"

class Pyramid_X_O_Board : public Board<char> {
public:
    Pyramid_X_O_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
    bool is_lose(Player<char>* p) override { return false; }
};

class Pyramid_X_O_UI : public UI<char> {
public:
    Pyramid_X_O_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif