#include "game.hpp" 
#include "playerClass.hpp"

Game::Game() {    // initialise a game (constructor)
    turn = 1;
    moves = 0;
    gameStatus = 0;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            grid[i][j] = 0;
        }
    }
}

void Game::printGrid() {  
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

void Game::apply(int i, int j) {       // return 2 for draw, -1 or 1 for the winner, 0 for game not finished
    if (grid[i][j] == 0) {     // can play only is the case (i,j) is empty
        grid[i][j] = turn;
        moves++;
        // cout << "applied move " << i << " " << j << "\n";
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
    else {
        cout << "Erreur : position invalise\n";
    }
}

void Game::unapply(int i, int j) {
    grid[i][j] = 0;
    turn = -turn;
    gameStatus = 0; 
    moves--;
    // cout << "unapplied move " << i << " " << j << "\n";
}

// to play a move, the grid is divided in 9 cases, a number from 0 to 8 going from top left to bottom right

vector<int> Game::getMoves() {
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

int Game::playMoves() {
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

// We define different functions to play the game : Human vs Human (with graphic interface), Human vs AI, AI vs AI 

// int playGameHH(HumanPlayer p1, HumanPlayer p2) {                // plays a game with graphic interface for Human, return -1 if -1 won, 1 if 1 won and 2 if it's a draw
//     Game g;
//     int coup = 0;
//     while (g.gameStatus == 0) {
//         g.printGrid();
//         coup = g.playMoves();
//         g.apply(coup/3,coup%3);
//     }
//     g.printGrid();
//     if (g.gameStatus != 2) {
//         cout << g.gameStatus << " a gagné la partie!" << "\n";
//         return g.gameStatus;
//     }
//     else {
//         cout << "Match nul !" << "\n";
//         return 2;
//     }
// }

int playGame() {                    // no output messages for bots -> faster 
    Game g;
    int coup = 0;
    while (g.gameStatus == 0) {
        cin >> coup;
        g.apply(coup/3,coup%3);
    }
    return g.gameStatus;
}


int playGameHuman() {                // plays a game with graphic interface for Human, return -1 if -1 won, 1 if 1 won and 2 if it's a draw
    Game g;
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

int playGameClass(Player& p1, Player& p2) {
    Game g; 
    int coup; 
    while (g.gameStatus == 0) {
        coup = g.turn == 1 ? p1.play(g) : p2.play(g);
        g.apply(coup/3, coup%3);
    }
    g.printGrid(); 
    switch (g.gameStatus) {
        case 2: 
            cout << "Match nul! \n";  
            break; 
        case 1: 
            cout << p1.name << " a gagné la partie! \n"; 
            break; 
        case -1: 
            cout << p2.name << " a gagné la partie! \n"; 
            break; 
    }
    return g.gameStatus; 
}