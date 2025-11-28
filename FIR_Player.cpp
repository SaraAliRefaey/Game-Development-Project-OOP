#include "FIR_Player.h"


FIR_Player::FIR_Player() {
    name = "";
    symbol = ' ';
    iscomputer = false;
}


FIR_Player::FIR_Player(string n, char s, bool isComp) {
    name = n;
    symbol = s;
    iscomputer = isComp;
}


FIR_Player::~FIR_Player() {}


string FIR_Player::getName() {
    return name;
}

char FIR_Player::getSymbol() {
    return symbol;
}

bool FIR_Player::getIsComputer() {
    return iscomputer;
}

void FIR_Player::setName(string n) {
    name = n;
}

void FIR_Player::setSymbol(char s) {
    symbol = s;
}

void FIR_Player::setIsComputer(bool isComp) {
    iscomputer = isComp;
}






