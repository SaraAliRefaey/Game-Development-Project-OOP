

#include "NumericalTTT_Player.h"
#include "BoardGame_Classes.h"

NumericalTTT_Player::NumericalTTT_Player(int id, bool is_human):Player<int>("Player " + to_string(id), id, (is_human ? PlayerType::HUMAN : PlayerType::COMPUTER)) {
    this->id = id;
    this->is_human = is_human;
    if (id==1) {
        available_numbers={1,3,5,7,9};
    }
    else if (id==2) {
        available_numbers={2,4,6,8};
    }
}
void NumericalTTT_Player::get_move(Move<int>& m, Board<int>& b) {
    int position,value;
    cout << "\n--- Player " << id << " Turn ---" << endl;
    cout << "Available numbers: ";
    for (int num : available_numbers) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Enter position (0-8): ";
    cin >> position;

    cout << "Enter value from your available numbers: ";
    cin >> value;

    while (!valid_move(value)) {
        cout << "Invalid choice! Please enter one of your available numbers: ";
        cin >> value;
    }

    remove_move(value);
    m=Move<int>(position/3,position%3,value);
    b.update_board(&m);
    bool valid = b.update_board(&m);
    if (!valid) {
        cout << " Invalid move, try again.\n";
    }
    cout << "Player " << id << " played value " << value << " at position " << position << endl;



}
bool NumericalTTT_Player::valid_move(int value) {
    if (value < 1 || value > 9) {
        return false;
    }

    for (int num:available_numbers) {
        if (value == num) {
            return true;
        }
    }
    return false;
}
void NumericalTTT_Player::remove_move(int value) {
    for (auto it = available_numbers.begin(); it != available_numbers.end(); it++) {
        if (*it == value) {
            available_numbers.erase(it);
            break;
        }
    }

}


NumericalTTT_Player::~NumericalTTT_Player() {

}


