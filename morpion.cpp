#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>



using std::cout, std::cin, std::endl, std::string, std::vector;

class Game {
public:

    int turn;        // which player is playing 
    int moves;       // number of mooves played 
    int grid[3][3];
    int gameStatus; // -1 if -1 won, 1 if 1 won, 2 if it's a draw, 0 if still going

    void init() {    // initialise a game
        turn = 1;
        moves = 0;
        gameStatus = 0;
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                grid[i][j] = 0;
            }
        }
    }

    void printGrid() {  
        for (auto& ligne : grid) {
            for (int x : ligne) {
                if (x == -1) {
                    cout << "O" << " ";
                }
                else if (x == 1) {
                    cout << "X" << " ";
                }
                else {
                    cout << "_" << " ";
                }
            }
            cout << "\n";
        }
        cout << "c'est au tour de " << turn << "\n";
    }

    // change the grid in place and checking game status 

    void apply(int i, int j) {       // return 2 for draw, -1 or 1 for the winner, 0 for game not finished
        if (grid[i][j] == 0) {     // can play only is the case (i,j) is empty
            grid[i][j] = turn;
            moves++;
            if (moves < 5) {       // useless to check if someone has won before 5 moves played
                turn = -turn;
                return; 
            }
            if (moves == 9) {
                gameStatus = 2;      // if the grid is full but no one won -> draw
            }
            if (grid[(i+1)%3][j] == turn && grid[(i+2)%3][j] == turn) {     // checking rows 
                gameStatus = turn;
            }
            if (grid[i][(j+1)%3] == turn && grid[i][(j+2)%3] == turn) {     // checking columns 
                gameStatus = turn;
            }
            if (i == 1 && j == 1) {     // middle case 
                if ((grid[0][0] == turn && grid[2][2] == turn) || (grid[2][0] == turn && grid[0][2] == turn)) {
                    gameStatus = turn;
                }
            }
            if (grid[1][1] == turn) {        // since we are checking the diagonals here, we check before the middle case else it's useless to continue
                switch (3*i+j) {
                    case 0:
                        if (grid[2][2] == turn) {
                            gameStatus = turn;
                        }
                        break;
                    case 6:
                        if (grid[0][2] == turn) {
                            gameStatus = turn;
                        }
                        break;
                    case 2:
                        if (grid[2][0] == turn) {
                            gameStatus = turn;
                        }
                        break;
                    case 8:
                        if (grid[0][0] == turn) {
                            gameStatus = turn;
                        }
                        break;
                }
            }
            turn = -turn;  // other player to play next move 
        } 
    }

    void unapply(int i, int j) {
        grid[i][j] = 0;
        turn = -turn;
        gameStatus = 0; 
        moves--;
    }
    
    // to play a move, the grid is divided in 9 cases, a number from 0 to 8 going from top left to bottom right

    vector<int> getMoves() {
        vector<int> possibleMoves;
        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++) {
                if (grid[i][j] == 0) {
                    possibleMoves.push_back(3*i+j);
                }
            }
        }
        return possibleMoves;
    }

    int playMoves() {
        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++) {
                if (grid[i][j] == 0) {
                    cout << 3*i+j << " : jouer (" << i << "," << j << ")\n";
                }
            }
        }
        int coup;
        cout << "Quel coup voulez vous jouer ?\n";
        cin >> coup;
        return coup;
    }

};

int playGameHuman() {                // plays a game with graphic interface for Human, return -1 if -1 won, 1 if 1 won and 2 if it's a draw
    Game g;
    g.init();
    int coup = 0;
    while (g.gameStatus == 0) {
        g.printGrid();
        coup = g.playMoves();
        g.apply(coup/3,coup%3);
    }
    g.printGrid();
    if (g.gameStatus != 2) {
        cout << g.gameStatus << " a gagné la partie!" << "\n";
        return g.gameStatus;
    }
    else {
        cout << "Match nul !" << "\n";
        return 2;
    }
}

int playGame() {                    // no output messages for bots -> faster 
    Game g;
    g.init();
    int coup = 0;
    while (g.gameStatus == 0) {
        coup = g.playMoves();
        g.apply(coup/3,coup%3);
    }
    return g.gameStatus;
}


class Player {                  // we need a function that takes a Game (a board) and return an allowed move - heuristic, min-max, alpha-beta
public: 

    void init(string name, int player, int maxDepth) {
        name = name;
        player = player;
        maxDepth = maxDepth;
    }

    vector<int> getPossibleMoves(Game g) {
        return g.getMoves();
    }

    float heuristic(Game g) {          // positive value -> favorable position, negative value -> unfavorable position

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

    }

    float alphabeta(Game g) {
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

    float minValue(Game g, int depth, float alpha, float beta) {
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

    float maxValue(Game g, int depth, float alpha, float beta) {
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


private:

    string name;
    int player = 0; 
    int maxDepth = 0;

};

int main() {
    playGame();    

        // Mesures de temps 

    // vector<vector<int>> m = init_rdm_matrix(1000);

    
    // auto start_time = chrono::high_resolution_clock::now();
    // vector<vector<int>> res = mult_naif(m, m);

    // auto end_time = chrono::high_resolution_clock::now();
    // auto time = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    // cout << "Time execution : " << (float)time.count()/1000 << " milisecondes" << endl; 

    // Tests 

    return 0;
}