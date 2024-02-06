#ifndef PLAYERAI_H
#define PLAYERAI_H

#include "game.h"
#include <limits>
#include <algorithm>


class HumanPlayer {
public:
    
    int player = 0;

    Player(string name, int player, int maxDepth);

private:
    string name;
};

class AIPlayer :  {

    int player = 0;

    AIPlayer(string name, int player, int maxDepth);

    float heuristic(Game &g);

    int alphabeta(Game &g);

    float minValue(Game &g, int depth, float alpha, float beta);

    float maxValue(Game &g, int depth, float alpha, float beta);


private:
    string name;
    int maxDepth = 3;
};

#endif 
