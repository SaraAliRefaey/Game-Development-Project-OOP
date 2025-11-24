#pragma once

#include "BoardGame_Classes.h" 

class SimplePlayer5x5 : public Player<char> {
public:
   
    SimplePlayer5x5(string n, char s, PlayerType t)
        : Player<char>(n, s, t) {}
    
};

// (Board)

class TicTacToe5x5_Board : public Board<char> {
private:
  
    int count_three_in_a_row(char symbol);

public:
   
    TicTacToe5x5_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>*) override;
    bool is_lose(Player<char>*) override;
    bool is_draw(Player<char>*) override;
    bool game_is_over(Player<char>*) override;
};



//  (UI)

class TicTacToe5x5_UI : public UI<char> {
public:
   
    TicTacToe5x5_UI();
  
    Move<char>* get_move(Player<char>*) override;
    
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};