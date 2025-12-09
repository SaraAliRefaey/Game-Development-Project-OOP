#include "UltimateBoard.h"
#include <iostream>
using namespace std;



SubBoard::SubBoard() {
    grid = vector<vector<char>>(3, vector<char>(3, '.'));
    state = SUB_IN_PROGRESS;
}

int SubBoard::getState() const {
    return state;
}

bool SubBoard::isFull() const {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (grid[r][c] == '.')
                return false;
    return true;
}

bool SubBoard::isValidMove(int r, int c) const {
    return (r >= 0 && r < 3 &&
            c >= 0 && c < 3 &&
            grid[r][c] == '.' &&
            state == SUB_IN_PROGRESS);
}

void SubBoard::placeMove(char symbol, int r, int c) {
    grid[r][c] = symbol;
    checkWin();

    if (state == SUB_IN_PROGRESS)
        checkDraw();
}

void SubBoard::checkWin() {
    for (int i = 0; i < 3; i++) {


        if (grid[i][0] != '.' &&
            grid[i][0] == grid[i][1] &&
            grid[i][1] == grid[i][2]) {

            state = (grid[i][0] == 'X') ? SUB_X_WON : SUB_O_WON;
            return;
        }


        if (grid[0][i] != '.' &&
            grid[0][i] == grid[1][i] &&
            grid[1][i] == grid[2][i]) {

            state = (grid[0][i] == 'X') ? SUB_X_WON : SUB_O_WON;
            return;
        }
    }

    if (grid[0][0] != '.' &&
        grid[0][0] == grid[1][1] &&
        grid[1][1] == grid[2][2]) {

        state = (grid[0][0] == 'X') ? SUB_X_WON : SUB_O_WON;
        return;
    }

    if (grid[0][2] != '.' &&
        grid[0][2] == grid[1][1] &&
        grid[1][1] == grid[2][0]) {

        state = (grid[0][2] == 'X') ? SUB_X_WON : SUB_O_WON;
        return;
    }
}

void SubBoard::checkDraw() {
    if (state == SUB_IN_PROGRESS && isFull())
        state = SUB_DRAW;
}

void SubBoard::reset() {
    grid = vector<vector<char>>(3, vector<char>(3, '.'));
    state = SUB_IN_PROGRESS;
}

UltimateBoard::UltimateBoard() : Board<char>(3, 3) {

    subboards = vector<vector<SubBoard>>(3, vector<SubBoard>(3));
    mainBoard = vector<vector<char>>(3, vector<char>(3, '.'));

    targetType = TARGET_ANY;
    targetR = -1;
    targetC = -1;
}


void UltimateBoard::displayBoard() const {

    cout << "\n=========== Ultimate Tic Tac Toe ===========\n";

    for (int br = 0; br < 3; br++) {
        for (int sr = 0; sr < 3; sr++) {

            for (int bc = 0; bc < 3; bc++) {

                const SubBoard& sb = subboards[br][bc];

                for (int sc = 0; sc < 3; sc++) {
                    cout << sb.grid[sr][sc] << " ";
                }

                cout << "| ";
            }

            cout << "\n";
        }

        cout << "-------------------------------------------\n";
    }

    cout << "Target: ";
    if (targetType == TARGET_ANY) cout << "ANY sub-board\n";
    else cout << "(" << targetR << "," << targetC << ")\n";

    cout << "===========================================\n";
}


bool UltimateBoard::isValidMove(int br, int bc, int r, int c) const {


    if (br < 0 || br >= 3 || bc < 0 || bc >= 3)
        return false;


    if (r < 0 || r >= 3 || c < 0 || c >= 3)
        return false;

    const SubBoard& sb = subboards[br][bc];

    if (sb.getState() != SUB_IN_PROGRESS)
        return false;

    if (!sb.isValidMove(r, c))
        return false;

    if (targetType == TARGET_SPECIFIC)
        if (br != targetR || bc != targetC)
            return false;

    return true;
}


void UltimateBoard::placeMove(char symbol, int br, int bc, int r, int c) {

    subboards[br][bc].placeMove(symbol, r, c);

    updateSubboardState(br, bc);
    calculateNextTarget(r, c);
}


void UltimateBoard::updateSubboardState(int br, int bc) {

    int st = subboards[br][bc].getState();

    if (st == SUB_X_WON)      mainBoard[br][bc] = 'X';
    else if (st == SUB_O_WON) mainBoard[br][bc] = 'O';
    else if (st == SUB_DRAW)  mainBoard[br][bc] = '-';
}


bool UltimateBoard::checkMainWin(char symbol) const {

    for (int r = 0; r < 3; r++)
        if (mainBoard[r][0] == symbol &&
            mainBoard[r][1] == symbol &&
            mainBoard[r][2] == symbol)
            return true;

    for (int c = 0; c < 3; c++)
        if (mainBoard[0][c] == symbol &&
            mainBoard[1][c] == symbol &&
            mainBoard[2][c] == symbol)
            return true;

    if (mainBoard[0][0] == symbol &&
        mainBoard[1][1] == symbol &&
        mainBoard[2][2] == symbol)
        return true;

    if (mainBoard[0][2] == symbol &&
        mainBoard[1][1] == symbol &&
        mainBoard[2][0] == symbol)
        return true;

    return false;
}


bool UltimateBoard::checkMainDraw() const {

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (mainBoard[r][c] == '.')
                return false;

    return true;
}


void UltimateBoard::calculateNextTarget(int r, int c) {

    int nr = r;
    int nc = c;

    if (subboards[nr][nc].getState() != SUB_IN_PROGRESS) {
        targetType = TARGET_ANY;
        return;
    }

    targetType = TARGET_SPECIFIC;
    targetR = nr;
    targetC = nc;
}


bool UltimateBoard::isTargetFree() const {

    if (targetType == TARGET_ANY)
        return true;

    return (subboards[targetR][targetC].getState() == SUB_IN_PROGRESS);
}


int UltimateBoard::getTargetType() const { return targetType; }
int UltimateBoard::getTargetR() const { return targetR; }
int UltimateBoard::getTargetC() const { return targetC; }


void UltimateBoard::resetBoard() {

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++) {
            subboards[r][c].reset();
            mainBoard[r][c] = '.';
        }

    targetType = TARGET_ANY;
    targetR = -1;
    targetC = -1;
}



bool UltimateBoard::update_board(Move<char>* move) {
    return true;
}


bool UltimateBoard::is_win(Player<char>* player) {
    return checkMainWin(player->get_symbol());
}

bool UltimateBoard::is_lose(Player<char>* player) {
    char s = player->get_symbol();
    char opp = (s == 'X') ? 'O' : 'X';
    return checkMainWin(opp);
}

bool UltimateBoard::is_draw(Player<char>* player) {
    return checkMainDraw();
}

bool UltimateBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}
