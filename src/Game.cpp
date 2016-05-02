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
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        //User requests quit
        if (e.type == SDL_QUIT) {
            running = false;
        }
            //User presses a key
        else if (e.type == SDL_KEYDOWN) {
            //Select surfaces based on key press
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
                break;
            } else {
                scene->notify(e);
            }
        }

    }

}

void Game::update() {
    scene->update(SDL_GetTicks());
}

void Game::draw() {

    scene->draw();

    SDL_UpdateWindowSurface(window);
    SDL_Delay(10);
}
