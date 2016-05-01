//
// Created by marian on 7.2.2016.
//

#include <iostream>
#include "Game.h"
#include "SceneFactory.h"
#include "Config.h"

void Game::init() {
    SDL_Init(SDL_INIT_VIDEO);

    Config config("../scripts/config.lua");
    //@todo read this from config
    m_window = SDL_CreateWindow(config.m_title.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                config.m_width, config.m_height,
                                SDL_WINDOW_OPENGL);

    if (NULL == m_window) {
        printf("Unable to create SDL window:%s\n", SDL_GetError());
        return;
    }

    m_isRunning = true;

    // prepare scene
    m_scene = SceneFactory::createScene(SDL_CreateRenderer(m_window, -1, 0), config.m_startingScene.c_str());

}

bool Game::isRunning() {
    return m_isRunning;
}

void Game::cleanUp() {

    if (nullptr != m_scene) {
        delete m_scene;
    }

    if (nullptr != m_window) {
        SDL_DestroyWindow(m_window);
    }
    SDL_Quit();
}

void Game::handleInput() {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        //User requests quit
        if (e.type == SDL_QUIT) {
            m_isRunning = false;
        }
            //User presses a key
        else if (e.type == SDL_KEYDOWN) {
            //Select surfaces based on key press
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                m_isRunning = false;
                break;
            } else {
                m_scene->notify(e);
            }
        }

    }

}

void Game::update() {
    m_scene->update(SDL_GetTicks());
}

void Game::draw() {

    m_scene->draw();

    SDL_UpdateWindowSurface(m_window);
    SDL_Delay(10);
}
