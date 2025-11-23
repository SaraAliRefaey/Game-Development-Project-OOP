
#ifndef NUMERICALTTT_PLAYER_H
#define NUMERICALTTT_PLAYER_H
#include "BoardGame_Classes.h"
#include "NumericalTTT_Board.h"
#include "NumericalTTT_Move.h"


class NumericalTTT_Player:public Player<int> {
private:
    int id;
    vector<int> available_numbers;
    bool is_human;
    public:
    NumericalTTT_Player(int id,  bool is_human);
   virtual  ~NumericalTTT_Player();
    void get_move(Move<int>& m, Board<int>& b) ;


    bool valid_move(int value);
    void remove_move(int value);



};



#endif //NUMERICALTTT_PLAYER_H
