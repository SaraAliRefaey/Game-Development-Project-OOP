#ifndef FOUR_BY_FOUR_TIC_TAC_TOE_H
#define FOUR_BY_FOUR_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"

class Four_by_Four_Board : public Board<char> {
public:
    Four_by_Four_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
    bool is_lose(Player<char>* p) override { return false; }
};

class Four_by_Four_UI : public UI<char> {
public:
    Four_by_Four_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif
