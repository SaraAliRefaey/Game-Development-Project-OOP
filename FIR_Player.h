
#ifndef FIR_PLAYER_H
#define FIR_PLAYER_H

#include <string>
using namespace std;

class FIR_Player {
private:
    string name;
    char symbol;
    bool iscomputer;
    public:
    FIR_Player();
    FIR_Player(string n, char s, bool isComp);
    ~FIR_Player();

    string getName();
    char getSymbol();
    bool getIsComputer();

    void setName(string n);
    void setSymbol(char s);
    void setIsComputer(bool isComp);
};



#endif //FIR_PLAYER_H
