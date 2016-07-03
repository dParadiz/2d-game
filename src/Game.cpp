#include <iostream>
#include "Game.h"
#include "SceneFactory.h"
#include "Config.h"

void Game::init() {
    SDL_Init(SDL_INIT_VIDEO);

    Config config;
    config.loadFromFile("../scripts/config.lua");

    window = SDL_CreateWindow(config.title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              config.width, config.height,
                              SDL_WINDOW_OPENGL);

    if (NULL == window) {
        printf("Unable to create SDL window:%s\n", SDL_GetError());
        return;
    }

    running = true;

    // prepare scene
    scene = SceneFactory::createScene(SDL_CreateRenderer(window, -1, 0), config.startingScene.c_str());

}

bool Game::isRunning() {
    return running;
}

void Game::cleanUp() {

    if (nullptr != scene) {
        delete scene;
    }

    if (nullptr != window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void Game::handleInput() {

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE]) {
        running = false;
        return;
    }


    scene->notify(state);
    SDL_PumpEvents();


}

void Game::update(uint32_t timeTick) {
    scene->update(timeTick);
}

void Game::draw() {

    scene->draw();

    SDL_UpdateWindowSurface(window);
    SDL_Delay(10);
}
