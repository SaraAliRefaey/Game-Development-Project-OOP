#ifndef SUS_UI_H
#define SUS_UI_H

#include "BoardGame_Classes.h"
#include "SUS_Player.h"

class SUS_UI : public UI<char> {

public:
    SUS_UI();

    Move<char>* get_move(Player<char>* player) override;

    Player<char>* create_player(string& name, char, PlayerType type) override;
};

#endif

