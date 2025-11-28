
#include "SUS_UI.h"
#include "SUS_Move.h"
#include <iostream>
using namespace std;

SUS_UI::SUS_UI()
        : UI<char>("Welcome to SUS Game!", 3) {}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    return dynamic_cast<SUS_Player*>(player)->get_move();
}

Player<char>* SUS_UI::create_player(string& name, char, PlayerType type) {
    return new SUS_Player(name, type);
}
