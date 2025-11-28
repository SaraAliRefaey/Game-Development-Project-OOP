
#ifndef SUS_PLAYER_H
#define SUS_PLAYER_H
#include "BoardGame_Classes.h"

class SUS_Player:public Player<char> {
private:
    int id;
    bool is_human;
public:
    SUS_Player(int id,  bool is_human);
   ~SUS_Player();
    void get_move(Move<char>& m, Board<char>& b)  ;

};



#endif //SUS_PLAYER_H
