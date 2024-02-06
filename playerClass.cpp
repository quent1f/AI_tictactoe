#include "playerClass.h"

/* 2 classes Player : HumanPlayer and AIPlayer */

HumanPlayer::HumanPlayer(string name, int player) {
    name = name;
    player = player;
}

    



AIPlayer::AIPlayer(string name, int player, int maxDepth) {
    name = name;
    player = player;
    maxDepth = maxDepth;
}

float AIPlayer::heuristic(Game &g) {          // positive value -> favorable position, negative value -> unfavorable position

    if (g.gameStatus == 0) {
        return 0;               // TODO 

    }

    if (g.gameStatus == player) {
        return std::numeric_limits<float>::max();
    }
    if (g.gameStatus == -player) {  
        return std::numeric_limits<float>::min();   
    }
    if (g.gameStatus == 2) {                            // draw case
        return 0;
    }
    return 0; 
}

int AIPlayer::alphabeta(Game &g) {                         // play the better move using alpha-beta pruning
    float best_score = std::numeric_limits<float>::min();
    float beta = std::numeric_limits<float>::max();
    int coup = -1;
    float value;
    vector<int> possibleMoves = g.getMoves();
    for (int action : possibleMoves) {
        g.apply(action/3, action%3);
        value = minValue(g, best_score, beta, 1);
        g.unapply(action/3, action%3);
        if (value > best_score) {
            best_score = value;
            coup = action; 
        }
    }
    if (coup == -1) {
        coup = possibleMoves[0];
    }
    return coup;
}

float AIPlayer::minValue(Game &g, int depth, float alpha, float beta) {
    if (depth > maxDepth || g.gameStatus != 0) {
        return heuristic(g);
    }
    float value = std::numeric_limits<float>::max();
    for (int action : g.getMoves()) {
        g.apply(action/3, action%3);
        value = std::min(value, maxValue(g, depth+1, alpha, beta));
        g.unapply(action/3, action%3);
        if (value <= alpha) {
            return value;
        }
        beta = std::min(beta, value);
    }
    return value;
}

float AIPlayer::maxValue(Game &g, int depth, float alpha, float beta) {
    if (depth > maxDepth || g.gameStatus != 0) {
        return heuristic(g);
    }
    float value = std::numeric_limits<float>::min();
    for (int action : g.getMoves()) {
        g.apply(action/3, action%3);
        value = std::max(value, maxValue(g, depth+1, alpha, beta));
        g.unapply(action/3, action%3);
        if (value >= alpha) {
            return value;
        }
        alpha = std::max(alpha, value);
    }
    return value;
}

