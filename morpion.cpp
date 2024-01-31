#include <iostream>

using std::cout, std::cin, std::endl;

class game {
public:
    int turn;
    int grid[3][3];

    void init() {
        turn = 1;
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
                if (x == 1) {
                    cout << "X" << " ";
                }
                else {
                    cout << "_" << " ";
                }
            }
            cout << "\n";
        }
        cout << "C'est au tour de " << turn << "\n";
    }

    void play(int i, int j) {
        if (grid[i][j] == 0) {
            grid[i][j] = turn;
            turn = -turn;
        }
    }

    

};


int main() {
    game g;
    g.init();
    g.play(0,0);
    g.play(1,1);
    g.printGrid();
    return 0;
}