#include <iostream>

using std::cout, std::cin, std::endl;

class Game {
public:
    int turn;        // which player is playing 
    int moves;       // number of mooves played 
    int grid[3][3];

    void init() {    // initialise a game
        turn = 1;
        moves = 0;
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

    int play(int i, int j) {       // return 2 for draw, -1 or 1 for the winner, 0 for game not finished
        if (grid[i][j] == 0) {     // can play only is the case (i,j) is empty
            grid[i][j] = turn;
            moves++;
            if (moves < 5) {       // useless to check if someone has won before 5 moves played
                turn = -turn;
                return 0;
            }
            if (grid[(i+1)%3][j] == turn && grid[(i+2)%3][j] == turn) {     // checking rows 
                return turn;
            }
            if (grid[i][(j+1)%3] == turn && grid[i][(j+2)%3] == turn) {     // checking columns 
                return turn;
            }
            if (i == 1 && j == 1) {     // middle case 
                if ((grid[0][0] == turn && grid[2][2] == turn) || (grid[2][0] == turn && grid[0][2] == turn)) return turn; 
            }
            if (grid[1][1] == turn) {        // since we are checking the diagonals here, we check before the middle case else it's useless to continue
                switch (i+3*j) {
                    case 0:
                        if (grid[2][2] == turn) return turn;
                        break;
                    case 6:
                        if (grid[2][0] == turn) return turn;
                        break;
                    case 2:
                        if (grid[0][2] == turn) return turn;
                        break;
                    case 8:
                        if (grid[0][0] == turn) return turn;
                        break;
                }
            }
            if (moves == 9) return 2;       // if the grid is full but no one won -> draw
            turn = -turn;   
        }
        return 0; 
    }

};


void playGame() {
    Game g;
    g.init();
    int i = 0, j = 0;
    g.printGrid();
    cout << "Que voulez-vous jouer ?" << "\n";
    cin >> i >> j;
    int gameState = g.play(i, j);
    while (gameState == 0) {
        g.printGrid();
        cout << "Que voulez-vous jouer ?" << "\n";
        cin >> i >> j;
        gameState = g.play(i,j);
    }
    g.printGrid();
    if (gameState != 2) {
        cout << gameState<< " a gagné la partie!" << "\n";
    }
    else {
        cout << "Match nul !" << "\n";
    }
}

int main() {
    playGame();    
    return 0;
}