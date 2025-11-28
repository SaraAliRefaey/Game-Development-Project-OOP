
#include "SUS_Player.h"
#include"BoardGame_Classes.h"
#include "SUS_Player.h"
#include "SUS_Board.h"
#include "SUS_Move.h"
using namespace std;
SUS_Player::SUS_Player(int id, bool is_human):Player<char>("Player " + to_string(id), id, (is_human ? PlayerType::HUMAN : PlayerType::COMPUTER)) {
    this->id = id;
    this->is_human = is_human;
}
void SUS_Player::get_move(Move<char>& m, Board<char>& b) {
    int position;
    char symbol;


    cout << "Enter position (0-8): ";
    cin >> position;

    cout << "Enter S or U: " << endl;
    cin >> symbol;
    while (symbol != 'S' && symbol != 'U') {
        cout << "Invalid symbol! Enter S or U: ";
        cin >> symbol;
    }
    SUS_Move* move = new SUS_Move();
    move->setPosition(position);
    move->setValue(symbol);

    bool valid = b.update_board(move);

    if (!valid) {
        cout << "Invalid move! Try again.\n";
    }

    m = Move<char>(position / 3, position % 3, symbol);

    delete move;

    cout << "Player " << id << " played " << symbol
         << " at position " << position << endl;

}

SUS_Player::~SUS_Player() {

}
