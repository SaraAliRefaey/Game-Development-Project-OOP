#pragma once
#include "BoardGame_Classes.h" 
#include <unordered_set>
#include <string>


class SimpleWordPlayer : public Player<char> {
public:
    
    SimpleWordPlayer(std::string n, char s, PlayerType t)
        : Player<char>(n, s, t) {}
};


class WordTicTacToe_Board : public Board<char> {
private:
    
    std::unordered_set<std::string> dictionary;

    
    void load_dictionary(const std::string& filename);

    
    bool check_for_word(char c1, char c2, char c3);

public:
   
    WordTicTacToe_Board();

  
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>*) override;
    bool is_lose(Player<char>*) override;
    bool is_draw(Player<char>*) override;
    bool game_is_over(Player<char>*) override;
};



class WordTicTacToe_UI : public UI<char> {
public:
  
    WordTicTacToe_UI();
    
    Move<char>* get_move(Player<char>*) override;
    
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};