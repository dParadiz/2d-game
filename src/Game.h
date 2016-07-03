#ifndef INC_2DGAME_GAME_H
#define INC_2DGAME_GAME_H

#include <SDL2/SDL.h>
#include "Scene.h"


class Game {
private:
    bool running = false;
    SDL_Window *window = nullptr;
    Scene *scene;
public:
    void init();

    void handleInput();

    void update(uint32_t timeTick);

    void draw();

    bool isRunning();

    void cleanUp();

};


#endif //INC_2DGAME_GAME_H
