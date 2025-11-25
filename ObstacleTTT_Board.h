#ifndef OBSTACLETTT_BOARD_H
#define OBSTACLETTT_BOARD_H

#include "BoardGame_Classes.h" // Provides Board, Player, and Move templates
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <string>

using namespace std;

/**
 * @brief Board class for Obstacles Tic-Tac-Toe on a 6x6 grid.
 * * Obstacles are placed randomly during construction (6 obstacles total). Players cannot use '#' cells.
 * Win condition is getting 3 in a row.
 */
class ObstacleTTT_Board : public Board<char> {
private:
    // Helper function to check if a specific symbol ('X' or 'O') has won 3-in-a-row.
    bool check_win_for_symbol(char symbol) const;

public:
    /**
     * @brief Constructor for the 6x6 Obstacles Tic-Tac-Toe board.
     * Initializes board and randomly places 6 obstacles ('#').
     */
    ObstacleTTT_Board();

    // Virtual function overrides from the base Board class
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_valid_move(Move<char>* move) ;
    void display_board();

};

#endif // OBSTACLETTT_BOARD_H