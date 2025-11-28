#ifndef FIR_GAME_H
#define FIR_GAME_H

#include "FIR_Board.h"
#include "FIR_Player.h"

class FIR_Game {
private:
    FIR_Board board;
    FIR_Player player1;
    FIR_Player player2;

public:
    FIR_Game();
    void startGame();
    void playTurn(FIR_Player& player);
};

#endif
