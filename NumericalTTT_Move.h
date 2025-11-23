
#ifndef NUMERICALTTT_MOVE_H
#define NUMERICALTTT_MOVE_H
#include"BoardGame_Classes.h"



class NumericalTTT_Move:public Move<int> {
private:
    int position;
    int value;
    public:
    NumericalTTT_Move();
    ~NumericalTTT_Move();

    int getPosition();
    int getValue();
    void setPosition(int a);
    void setValue(int a);


};



#endif //NUMERICALTTT_MOVE_H
