#include "ObstacleTTT_Board.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// Define the board dimensions for clarity
const int OBSTACLE_ROWS = 6;
const int OBSTACLE_COLS = 6;
const int OBSTACLE_COUNT = 6;

/**
 * @brief Constructor for Obstacle Tic-Tac-Toe Board.
 * Initializes a 6x6 board and places 6 obstacles randomly.
 */
ObstacleTTT_Board::ObstacleTTT_Board()
    // Initialize the base Board<char> with 6 rows and 6 columns
    : Board<char>(OBSTACLE_ROWS, OBSTACLE_COLS)
{
    // Initialize the 6x6 board with empty spaces
    for (int i = 0; i < rows; ++i) {
        board[i].assign(columns, ' ');
    }

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    int placed_obstacles = 0;
    while (placed_obstacles < OBSTACLE_COUNT) {
        int r = rand() % rows;
        int c = rand() % columns;

        // Check if the cell is already occupied (should be ' ')
        if (board[r][c] == ' ') {
            board[r][c] = '#'; // '#' represents an obstacle
            placed_obstacles++;
        }
    }

    // Reset number of moves counter in the base class (n_moves)
    n_moves = 0;
}

/**
 * @brief Displays the 6x6 Obstacle Tic-Tac-Toe board to the console.
 */
void ObstacleTTT_Board::display_board() {
    std::cout << "\n  | 0 | 1 | 2 | 3 | 4 | 5 |\n";
    std::cout << "---------------------------------\n";
    for (int i = 0; i < rows; ++i) {
        std::cout << i << " |";
        for (int j = 0; j < columns; ++j) {
            // Print the content of the cell (X, O, #, or ' ')
            // setw(2) ensures consistent spacing for single characters
            std::cout << std::setw(2) << board[i][j] << " |";
        }
        std::cout << "\n---------------------------------\n";
    }
}

/**
 * @brief Checks if a move is valid without updating the board.
 * @return true if the cell is within bounds, is not an obstacle, and is empty.
 * This is used by the Random Player to efficiently find a legal spot.
 */
bool ObstacleTTT_Board::is_valid_move(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();

    // 1. Check bounds
    if (r < 0 || r >= rows || c < 0 || c >= columns) {
        return false;
    }

    // 2. Check if cell is empty or an obstacle. A move is valid only if it's empty (' ').
    // Obstacles ('#') are invalid targets for a move.
    if (board[r][c] != ' ') {
        return false;
    }

    // If it is in bounds and empty, it is valid
    return true;
}


bool ObstacleTTT_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    // 1. Check bounds
    if (r < 0 || r >= rows || c < 0 || c >= columns) {
        std::cout << "Invalid move: Out of bounds (0-5 for row/col).\n";
        return false;
    }

    // 2. Check if cell is empty
    if (board[r][c] != ' ') {
        if (board[r][c] == '#') {
            std::cout << "Invalid move: Cell is blocked by an obstacle ('#').\n";
        } else {
            std::cout << "Invalid move: Cell is already taken by " << board[r][c] << ".\n";
        }
        return false;
    }

    // 3. Update board
    board[r][c] = symbol;
    n_moves++;
    return true;
}

/**
 * @brief Checks if the game ends in a win for the current player.
 * Checks for 3 consecutive symbols (X or O) horizontally, vertically, or diagonally.
 * Obstacles ('#') break a line but do not count as a move.
 */
bool ObstacleTTT_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();
    const int WIN_CONDITION = 3;

    // Helper to check for a line of length 'WIN_CONDITION'
    auto checkLine = [&](int r, int c, int dr, int dc) {
        int count = 0;
        for (int k = 0; k < WIN_CONDITION; ++k) {
            int current_r = r + k * dr;
            int current_c = c + k * dc;

            // Check bounds (should not be needed if loops are correct, but good safety)
            if (current_r < 0 || current_r >= rows || current_c < 0 || current_c >= columns) return false;

            // If the symbol matches, increment count
            if (board[current_r][current_c] == s) {
                count++;
            } else {
                // If anything else (opponent or empty/obstacle), the line is broken
                return false;
            }
        }
        return count == WIN_CONDITION;
    };

    // Iterate through all possible starting points for a 3-in-a-row line
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            // Check Horizontal: (1, 0) direction
            if (c <= columns - WIN_CONDITION && checkLine(r, c, 0, 1)) return true;

            // Check Vertical: (0, 1) direction
            if (r <= rows - WIN_CONDITION && checkLine(r, c, 1, 0)) return true;

            // Check Diagonal Down-Right: (1, 1) direction
            if (r <= rows - WIN_CONDITION && c <= columns - WIN_CONDITION && checkLine(r, c, 1, 1)) return true;

            // Check Diagonal Up-Right: (-1, 1) direction
            if (r >= WIN_CONDITION - 1 && c <= columns - WIN_CONDITION && checkLine(r, c, -1, 1)) return true;
        }
    }
    return false;
}

/**
 * @brief Checks if the board is full (all non-obstacle cells are filled).
 */
bool ObstacleTTT_Board::is_draw(Player<char>* player) {
    if (is_win(player)) return false;

    // Check if total number of non-obstacle cells have been filled (6*6 - 6 obstacles = 30)
    return n_moves >= (rows * columns - OBSTACLE_COUNT);
}

/**
 * @brief Checks if the game is over (win, lose, or draw).
 */
bool ObstacleTTT_Board::game_is_over(Player<char>* player) {
    // We only need to check is_win and is_draw, as is_lose is typically defined via is_win of the opponent.
    if (is_win(player)) return true;

    // To check if the *opponent* has won, we must manually check
    char opponent_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> opponent("Opponent", opponent_symbol, PlayerType::HUMAN);
    if (is_win(&opponent)) return true;

    // Check for draw (board full)
    return is_draw(player);
}

/**
 * @brief Checks if the current player has lost (i.e., the opponent has won).
 */
bool ObstacleTTT_Board::is_lose(Player<char>* player) {
    char opponent_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> opponent("Opponent", opponent_symbol, PlayerType::HUMAN);

    // The player loses if the opponent has won
    return is_win(&opponent);
}