    #include "playerClass.hpp"

    /* 2 classes Player : HumanPlayer and AIPlayer */

    int HumanPlayer::play(Game &g) {
        g.printGrid();
        return g.playMoves();
    }
        

    int AIPlayer::play(Game &g) {
        cout << name << " est entrain de réfléchir\n"; 
        return alphabeta(g); 
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

    // float AIPlayer::heuristic(Game &g) {              // positive value -> favorable position, negative value -> unfavorable position

    // if (g.gameStatus == player) return 1000.0;
    // if (g.gameStatus == -player) return -1000.0;
    // if (g.gameStatus == 2) return 0.0;               // Draw

    // float score = 0.0;

    // // Exemple d'heuristique simple : centralité
    // for (int i = 0; i < 3; ++i) {
    //     for (int j = 0; j < 3; ++j) {
    //         if (g.grid[i][j] == player) score += (i == 1 && j == 1) ? 3 : 1;
    //         if (g.grid[i][j] == -player) score -= (i == 1 && j == 1) ? 3 : 1;
    //     }
    // }
    // return score;
    // }



    int AIPlayer::alphabeta(Game &g) {
        float best_score = -std::numeric_limits<float>::infinity(); 
        float beta = std::numeric_limits<float>::infinity();
        int coup = -1;

        vector<int> possibleMoves = g.getMoves();
        if (possibleMoves.empty()) {
            throw std::runtime_error("No possible moves!");
        }

        for (int action : possibleMoves) {
            g.apply(action / 3, action % 3);
            float value = minValue(g, 1, best_score, beta); 
            g.unapply(action / 3, action % 3);

            cout << action << " " << value << " " << best_score << "\n"; 

            if (value > best_score) {
                best_score = value;
                coup = action;
            }
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
            if (value >= beta) {
                return value;
            }
            alpha = std::max(alpha, value);
        }
        return value;
    }

