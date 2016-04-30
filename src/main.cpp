#include <iostream>
#include "Game.h"


using namespace std;

int main() {

    Game game;

    game.init();

    //game loop
    while (game.isRunning()) {
        game.handleInput();
        game.update();
        game.draw();
    }

    game.cleanUp();

    return 0;
}