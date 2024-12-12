#pragma once

#include <iostream>
#include <vector>
#include "playerClass.hpp"

using std::cout, std::cin, std::endl, std::string, std::vector;

class Player; 

class Game {
public:

    int turn;        // which player is playing 
    int moves;       // number of mooves played 
    int grid[3][3];
    int gameStatus; // -1 if -1 won, 1 if 1 won, 2 if it's a draw, 0 if still going

    Game();

    void printGrid();

    void apply(int i, int j);

    void unapply(int i, int j);

    std::vector<int> getMoves();

    int playMoves();
};


int playGameHuman();

int playGame();



int playGameClass(Player& p1, Player& p2); 

