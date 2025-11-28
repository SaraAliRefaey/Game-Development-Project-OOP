
#ifndef SUS_BOARD_H
#define SUS_BOARD_H

#include "BoardGame_Classes.h"
#include "SUS_Move.h"
#include <vector>
using namespace std;

class SUS_Board :public Board<char>{

    private:
        vector< vector<char>> board;


    public:
        SUS_Board();
        ~SUS_Board();

        bool update_board(Move<char>* move) override;
        bool is_win(Player<char>* player) override;
        bool is_lose(Player<char>* player) override;
        bool is_draw(Player<char>* player) override;
        bool game_is_over(Player<char>* player) override;
        void display_board();

};
#endif //SUS_BOARD_H
