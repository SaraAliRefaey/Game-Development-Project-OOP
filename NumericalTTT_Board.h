
#ifndef NUMERICALTTT_BOARD_H
#define NUMERICALTTT_BOARD_H
#include "BoardGame_Classes.h"
using namespace std;
//This class represents the board for the Numerical Tic Tac Toe game.
class NumericalTTT_Board:public Board<int> {
private:
    vector< vector<int>> board;
    int winType;
    int winIndex;


    public:
    NumericalTTT_Board();
    ~NumericalTTT_Board();
  // void update_Board(Move<int>* move);
  //   bool is_win();
  //   bool is_draw();
  //   bool game_is_over();

    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* player) override;
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
    void display_board();
    void highlight_winning_line();



};


#endif //NUMERICALTTT_BOARD_H
