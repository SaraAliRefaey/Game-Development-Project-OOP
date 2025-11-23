
#include "NumericalTTT_Move.h"
#include "BoardGame_Classes.h"


NumericalTTT_Move::NumericalTTT_Move() : Move<int>(0, 0, 0), position(0), value(0) {

};

NumericalTTT_Move::~NumericalTTT_Move() {

}


int NumericalTTT_Move::getPosition() {
    return position;
}

int NumericalTTT_Move::getValue() {
    return value;
}

void NumericalTTT_Move::setPosition(int a) {
    position = a;
}

void NumericalTTT_Move::setValue(int a) {
    value = a;
}

