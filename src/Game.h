//
// Created by marian on 7.2.2016.
//

#ifndef INC_2DGAME_GAME_H
#define INC_2DGAME_GAME_H

#include <SDL2/SDL.h>
#include "Scene.h"


class Game {
private:
    bool m_isRunning = false;
    SDL_Window *m_window = nullptr;
    Scene *m_scene;
public:
    void init();

    void handleInput();

    void update();

    void draw();

    bool isRunning();

    void cleanUp();

};


#endif //INC_2DGAME_GAME_H
