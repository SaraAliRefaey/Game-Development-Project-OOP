//
// Created by DELL on 11/23/2025.
//

#include "SUS_Move.h"
#include "BoardGame_Classes.h"


SUS_Move::SUS_Move() : Move<char>(0, 0, '-'), position(0), value('-') {

};

SUS_Move::~SUS_Move() {

}



int SUS_Move::getPosition() {
    return position;
}

char SUS_Move::getValue() {
    return value;
}

void SUS_Move::setPosition(int p) {
    position = p;
}

void SUS_Move::setValue(char a) {
    value = a;
}