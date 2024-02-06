#ifndef PLAYERAI_H
#define PLAYERAI_H

#include "game.h"
#include <limits>
#include <algorithm>


class Player {
public:
    
    Player(string name, int player, int maxDepth);

    std::vector<int> getPossibleMoves(Game g);        // Maybe have to remove ? getMoves does the same since we get which player has to play in memory

    float heuristic(Game g);

    float alphabeta(Game g);

    float minValue(Game g, int depth, float alpha, float beta);

    float maxValue(Game g, int depth, float alpha, float beta);

private:

    string name;
    int player = 0; 
    int maxDepth = 0;

};


#endif 
