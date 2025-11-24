#include "TTT_5X5_Classes.h"
#include <iostream>
#include <algorithm> 

TicTacToe5x5_Board::TicTacToe5x5_Board()

    : Board<char>(5, 5)
{
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j] = ' ';
        }
    }
}

bool TicTacToe5x5_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != ' ') {
        return false;
    }

  
    board[x][y] = symbol;
    n_moves++;
    return true;
}

int TicTacToe5x5_Board::count_three_in_a_row(char symbol) {
    int count = 0;

   
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {

            
            if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol) {
                count++;
            }

            
            if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol) {
                count++;
            }

           
            if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol) {
                count++;
            }
        }
    }

   
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 2; j < columns; ++j) {
            if (board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol) {
                count++;
            }
        }
    }

    return count;
}

bool TicTacToe5x5_Board::game_is_over(Player<char>*) {
    return n_moves >= (rows * columns) - 1;
}

bool TicTacToe5x5_Board::is_win(Player<char>* player) {
    if (!game_is_over(player)) {
        return false;
    }

    char player_symbol = player->get_symbol();
    char opponent_symbol = (player_symbol == 'X') ? 'O' : 'X';

    int player_score = count_three_in_a_row(player_symbol);
    int opponent_score = count_three_in_a_row(opponent_symbol);

    return player_score > opponent_score; 
}


bool TicTacToe5x5_Board::is_draw(Player<char>* player) {
    if (!game_is_over(player)) {
        return false;
    }

    char player_symbol = player->get_symbol();
    char opponent_symbol = (player_symbol == 'X') ? 'O' : 'X';

    int player_score = count_three_in_a_row(player_symbol);
    int opponent_score = count_three_in_a_row(opponent_symbol);

    return player_score == opponent_score; 
}


bool TicTacToe5x5_Board::is_lose(Player<char>* player) {
    if (!game_is_over(player)) {
        return false;
    }

    char player_symbol = player->get_symbol();
    char opponent_symbol = (player_symbol == 'X') ? 'O' : 'X';

    int player_score = count_three_in_a_row(player_symbol);
    int opponent_score = count_three_in_a_row(opponent_symbol);

    return player_score < opponent_score; 
}



TicTacToe5x5_UI::TicTacToe5x5_UI()
    : UI<char>("Welcome to 5x5 Tic Tac Toe! The goal is to get the most three-in-a-row sequences.", 4)
{
}


Move<char>* TicTacToe5x5_UI::get_move(Player<char>* player) {
    int x, y;
    cout << "\nPlayer " << player->get_name() << " (" << player->get_symbol() << "), enter your move (row and column, 0 to 4): ";
    cin >> x >> y;

   
    return new Move<char>(x, y, player->get_symbol());
}


Player<char>* TicTacToe5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    
    return new SimplePlayer5x5(name, symbol, type);
}