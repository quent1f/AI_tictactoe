#include "src/game.hpp"
#include "src/playerClass.hpp"

int main() {

    AIPlayer AI1("AI1", 1, 3);
    AIPlayer AI2("AI2", -1, 5);

    HumanPlayer p1("Quent1", 1);
    HumanPlayer p2("Quent2", -1);

    playGameClass(AI1, AI2);
    return 0;
}


