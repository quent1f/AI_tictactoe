#include "src/game.hpp"
#include "src/playerClass.hpp"

int main() {

    // AIPlayer AI1("AI1", -1, 2);
    // AIPlayer AI2("AI2", 1, 2);

    HumanPlayer p1("Quentin1", 1);
    HumanPlayer p2("Quentin2", -1);
    playGameClass(p1, p2);
    return 0;
}


