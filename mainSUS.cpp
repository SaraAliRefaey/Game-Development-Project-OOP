#include "SUS_Board.h"
#include "SUS_UI.h"
#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

int main() {

    SUS_UI* ui = new SUS_UI();

    cout << "Setting up players...\n";

    // BoardGame_Classes UI already supports:
    // name + type selection automatically
    Player<char>** players = ui->setup_players();

    // Create board
    SUS_Board* board = new SUS_Board();

    // Plug into manager
    GameManager<char> manager(board, players, ui);

    // Run game
    manager.run();

    // Clean up
    delete board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;

    return 0;
}
