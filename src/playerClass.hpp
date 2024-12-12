#pragma once

#include "game.hpp"
#include <limits>
#include <algorithm>

using std::cout, std::cin, std::endl, std::string, std::vector;

class Game; 

class Player {

public:
    string name; 
    int player; 

    Player(const string& playerName, int playerNumber) : name(playerName), player(playerNumber) {}

    virtual int play(Game& g) = 0;       // juste pour avoir HumanPlayer::getNextMove et AIplayer::getNextMove

    virtual ~Player() {}
};


class HumanPlayer : public Player{
public:
    
    HumanPlayer(string playerName, int playerNumber) : Player(playerName, playerNumber) {};

    int play(Game& g); 

};


class AIPlayer : public Player {

public:

    int maxDepth; 

    AIPlayer(string AIname, int playerNumber, int maxDepth) : Player(AIname, playerNumber), maxDepth(maxDepth) {};

    int play(Game& g); 


    float heuristic(Game& g);

    int alphabeta(Game& g);

    float minValue(Game& g, int depth, float alpha, float beta);

    float maxValue(Game& g, int depth, float alpha, float beta);

};
