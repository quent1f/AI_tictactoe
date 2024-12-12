#include "src/playerClass.hpp"

// This file provides many differents tests sets in order to test heuristics and alpha-beta evaluations in different positions 


// int playGameAI(Game &g, AIPlayer p1, AIPlayer p2) {                    // no output messages for bots -> faster 
//     int coup = 0;
//     while (g.gameStatus == 0) {
//         if (g.turn == p1.player) {
//             coup = p1.alphabeta(g);
//         }
//         else {
//             coup = p2.alphabeta(g);
//         }
//         g.apply(coup/3,coup%3);
//     }
//     return g.gameStatus;
// }

int main() {

    Game g1; 
    g1.apply(0,0);
    g1.apply(1,1);
    g1.apply(2,0);

    /* Grid: 
        X _ _ 
        _ O _ 
        X _ _

    Turn : -1 (O), gameStatus : 0, moves : 3 
    */

    // Game g2;

    // g2.apply(0,0);
    // g2.apply(1,1);
    // g2.apply(2,0);
    // g2.apply(1,2);
    // g2.apply(1,0);

    // g2.printGrid();
    // cout << g2.turn << " " << g2.gameStatus << " " << g2.moves << "\n";

    Game g;
    AIPlayer AI1("AI1", -1, 2);
    AIPlayer AI2("AI2", 1, 2);

    playGameAI(g, AI1, AI2);
    g.printGrid();
    cout << g.turn << " " << g.gameStatus << " " << g.moves << "\n";

    return 0;

}