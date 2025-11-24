#include "Word_TTT_Classes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype> 


void WordTicTacToe_Board::load_dictionary(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open dictionary file: " << filename << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
       
        for (char& c : word) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        dictionary.insert(word);
    }
    file.close();

    std::cout << "Loaded " << dictionary.size() << " words from dictionary." << std::endl;
}


WordTicTacToe_Board::WordTicTacToe_Board()

    : Board<char>(3, 3)
{
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j] = ' ';
        }
    }

    load_dictionary("dic.txt");
}


bool WordTicTacToe_Board::check_for_word(char c1, char c2, char c3) {
    
    if (c1 == ' ' || c2 == ' ' || c3 == ' ') {
        return false;
    }
  
    std::string word;
    word += static_cast<char>(std::toupper(static_cast<unsigned char>(c1)));
    word += static_cast<char>(std::toupper(static_cast<unsigned char>(c2)));
    word += static_cast<char>(std::toupper(static_cast<unsigned char>(c3)));
      
    return dictionary.count(word) > 0;
}

bool WordTicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol(); 

    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != ' ') {
        return false;
    }

    
    if (!std::isalpha(static_cast<unsigned char>(symbol))) {
        return false;
    }

    
    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool WordTicTacToe_Board::is_win(Player<char>*) {

    // الأفقي والعمودي والقطري (أسفل يمين)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {

            // 1. أفقي (Horizontal)
            if (j <= columns - 3 && check_for_word(board[i][j], board[i][j + 1], board[i][j + 2])) {
                return true;
            }

            // 2. عمودي (Vertical)
            if (i <= rows - 3 && check_for_word(board[i][j], board[i + 1][j], board[i + 2][j])) {
                return true;
            }

            // 3. قطري (Diagonal Down-Right)
            if (i <= rows - 3 && j <= columns - 3 &&
                check_for_word(board[i][j], board[i + 1][j + 1], board[i + 2][j + 2])) {
                return true;
            }
        }
    }

    
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 2; j < columns; ++j) { 
            if (check_for_word(board[i][j], board[i + 1][j - 1], board[i + 2][j - 2])) {
                return true;
            }
        }
    }

   
    return false;
}


bool WordTicTacToe_Board::game_is_over(Player<char>* player) {
    
    if (is_win(player)) {
        return true;
    }

 
    return n_moves >= rows * columns;
}

bool WordTicTacToe_Board::is_draw(Player<char>* player) {

    return !is_win(player) && n_moves >= rows * columns;
}

bool WordTicTacToe_Board::is_lose(Player<char>* player) {
    
    return false;
}

WordTicTacToe_UI::WordTicTacToe_UI()
    : UI<char>("Welcome to Word Tic Tac Toe! Form a valid 3-letter word to win!", 4)
{
}

Move<char>* WordTicTacToe_UI::get_move(Player<char>* player) {
    int x, y;
    char letter;
    std::string input;

 
    std::cout << "\nPlayer " << player->get_name() << ", enter your move (row, col, and one letter): ";

    
    if (!(std::cin >> x >> y >> letter)) {
      
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input format. Please enter row, column, and a single letter." << std::endl;
        
        return new Move<char>(-1, -1, ' ');
    }

    
    return new Move<char>(x, y, letter);
}

Player<char>* WordTicTacToe_UI::create_player(std::string& name, char symbol, PlayerType type) {
    
    return new SimpleWordPlayer(name, symbol, type);
}