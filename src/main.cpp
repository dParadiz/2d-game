#include <iostream>
#include <unistd.h>
#include "Game.h"


using namespace std;

int main() {

    Game game;

    game.init();
    auto prevTimeTick = 0;
    int fps = 1000/64;
    //game loop
    while (game.isRunning()) {
        auto timeTick = SDL_GetTicks();
        if (timeTick - prevTimeTick > fps) {
            game.handleInput();
            game.update(timeTick);
            game.draw();
        } else {
            usleep(fps - (timeTick - prevTimeTick));
        }

    }

    game.cleanUp();

    return 0;
}