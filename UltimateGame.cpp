#include "UltimateGame.h"
using namespace std;


UltimateGame::UltimateGame(bool vsComputer) {

    againstComputer = vsComputer;

    XO_UI ui;

    string name1 = "Player 1";
    string name2 = "Player 2";


    player1 = ui.create_player(name1, 'X', PlayerType::HUMAN);

    if (againstComputer)
        player2 = ui.create_player(name2, 'O', PlayerType::COMPUTER);
    else
        player2 = ui.create_player(name2, 'O', PlayerType::HUMAN);

    currentSymbol = 'X';
}


void UltimateGame::printInstructions() const {
    cout << "\n===== Ultimate Tic Tac Toe =====\n";
    cout << "Rules:\n";
    cout << "1. The game has 9 mini-boards (3x3).\n";
    cout << "2. You must play inside the mini-board determined by your opponent.\n";
    cout << "3. If the target mini-board is finished, you can play ANYWHERE.\n";
    cout << "4. Win 3 mini-boards in a row to win the game!\n\n";
}


void UltimateGame::printTurnInfo() const {
    cout << "Current Player: " << currentSymbol << "\n";

    if (board.getTargetType() == TARGET_ANY)
        cout << "Target: ANY sub-board\n\n";
    else
        cout << "Target: (" << board.getTargetR()
             << "," << board.getTargetC() << ")\n\n";
}


bool UltimateGame::readMove(int &br, int &bc, int &r, int &c) const {

    cout << "Enter main board row (0-2): ";
    cin >> br;

    cout << "Enter main board col (0-2): ";
    cin >> bc;

    cout << "Enter sub-board row (0-2): ";
    cin >> r;

    cout << "Enter sub-board col (0-2): ";
    cin >> c;

    return true;
}



void UltimateGame::playTurn() {

    board.displayBoard();
    printTurnInfo();

    int br, bc, r, c;

    // COMPUTER TURN
    if (currentSymbol == 'O' && againstComputer) {

        cout << "Computer thinking...\n";

        bool done = false;

        for (int i = 0; i < 3 && !done; i++) {
            for (int j = 0; j < 3 && !done; j++) {
                for (int rr = 0; rr < 3 && !done; rr++) {
                    for (int cc = 0; cc < 3 && !done; cc++) {

                        if (board.isValidMove(i, j, rr, cc)) {
                            br = i; bc = j;
                            r = rr; c = cc;
                            done = true;
                        }
                    }
                }
            }
        }

        cout << "Computer plays: (" << br << "," << bc
             << ") -> (" << r << "," << c << ")\n";
    }
    else {

        // HUMAN TURN
        cout << "Your turn (" << currentSymbol << ")\n";
        readMove(br, bc, r, c);
    }

    if (!board.isValidMove(br, bc, r, c)) {
        cout << "Invalid move! Try again.\n";
        return;
    }

    board.placeMove(currentSymbol, br, bc, r, c);

    switchPlayer();
}


void UltimateGame::switchPlayer() {

    if (currentSymbol == 'X')
        currentSymbol = 'O';
    else
        currentSymbol = 'X';
}



bool UltimateGame::checkGameEnd() {

    if (board.checkMainWin('X')) {
        board.displayBoard();
        cout << "\nPlayer X WINS!\n";
        return true;
    }

    if (board.checkMainWin('O')) {
        board.displayBoard();
        cout << "\nPlayer O WINS!\n";
        return true;
    }

    if (board.checkMainDraw()) {
        board.displayBoard();
        cout << "\nDRAW!\n";
        return true;
    }

    return false;
}



void UltimateGame::run() {

    printInstructions();

    board.resetBoard();

    while (!checkGameEnd()) {
        playTurn();
    }
}
