#include "FIR_Game.h"
#include <iostream>
using namespace std;

FIR_Game::FIR_Game() {
    string name1, name2;
    char symbol1 = 'X', symbol2 = 'O';
    int mode;

    cout << "Choose game mode:\n1. Player vs Player\n2. Player vs Computer\nEnter: ";
    cin >> mode;

    cout << "Enter Player 1 name: ";
    cin >> name1;

    if (mode == 1) {
        cout << "Enter Player 2 name: ";
        cin >> name2;

        player1 = FIR_Player(name1, symbol1, false);
        player2 = FIR_Player(name2, symbol2, false);
    }
    else {
        cout << "Computer will play as O\n";
        player1 = FIR_Player(name1, symbol1, false);
        player2 = FIR_Player("Computer", symbol2, true);
    }
}

void FIR_Game::playTurn(FIR_Player& player) {
    int col;

    board.printBoard();
    cout << player.getName() << " (" << player.getSymbol() << ") choose column (0-6): ";

    if (player.getIsComputer()) {
        col = rand() % 7;
        cout << col << endl;
    } else {
        cin >> col;
    }

    while (!board.makeMove(col, player.getSymbol())) {
        cout << "Invalid move. Try again: ";
        cin >> col;
    }
}

void FIR_Game::startGame() {
    FIR_Player* current = &player1;

    while (true) {
        playTurn(*current);

        if (board.checkWin(current->getSymbol())) {
            board.printBoard();
            cout << current->getName() << " WINS!\n";
            break;
        }

        if (board.isBoardFull()) {
            board.printBoard();
            cout << "DRAW!\n";
            break;
        }

        // Switch players
        current = (current == &player1) ? &player2 : &player1;
    }
}
