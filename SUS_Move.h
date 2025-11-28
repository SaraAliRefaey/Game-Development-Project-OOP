//
// Created by DELL on 11/23/2025.
//

#ifndef SUS_MOVE_H
#define SUS_MOVE_H

#include"BoardGame_Classes.h"



class SUS_Move:public Move<char> {
private:
    int position;
    int value;
public:
    SUS_Move();
    ~SUS_Move();

    int getPosition();
    char getValue();
    void setPosition(int p);
    void setValue(char a);


};


#endif //SUS_MOVE_H
