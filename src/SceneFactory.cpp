//
// Created by dejan on 25.2.2016.
//
#include <iostream>
#include <stdexcept>


#include "SceneFactory.h"

SDL_Rect SceneFactory::getRect(lua_State *L, int index) {
    int d[4] = {0, 0, 0, 0}, i = 0;
    if (lua_istable(L, index)) {
        lua_pushnil(L);

        for (i = 0; i < 4; i++) {
            lua_next(L, -2);
            d[i] = (int) lua_tonumber(L, -1);
            lua_pop(L, 1);
        }

        lua_pop(L, 1);
    }
    return SDL_Rect{d[0], d[1], d[2], d[3]};
}

void SceneFactory::loadTextures(lua_State *L, Scene *t_scene) {
    // load textures
    lua_getglobal(L, "textures");
    if (!lua_istable(L, -1)) {
        std::cout << "textures are not table " << std::endl;
    }

    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {

        if (lua_isstring(L, -1)) {
            SDL_Surface *image = SDL_LoadBMP(lua_tostring(L, -1));
            if (nullptr == image) {
                std::cout << "Could not load image: " << SDL_GetError() << std::endl;
            } else {
                SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 105, 74, 46));
                t_scene->addTexture(lua_tostring(L, -2), SDL_CreateTextureFromSurface(t_scene->getRenderer(), image));
            }
            SDL_FreeSurface(image);
        }

        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}

Scene *SceneFactory::createScene(SDL_Renderer *t_renderer, const char *sceneScript) {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_loadfile(L, sceneScript) || lua_pcall(L, 0, 0, 0)) {
        throw std::runtime_error(strcat((char *) "Error scene script: ", lua_tostring(L, -1)));
    }

    // prepare scene rendered for scene -- TODO get color form lua
    SDL_SetRenderDrawColor(t_renderer, 105, 74, 46, 255);
    SDL_RenderClear(t_renderer);
    SDL_SetRenderDrawBlendMode(t_renderer, SDL_BLENDMODE_BLEND);

    Scene *scene = new Scene(t_renderer);

    SceneFactory::loadTextures(L, scene);
    // SceneFactory::loadAnimations(L, scene);
    SceneFactory::loadSprites(L, scene);

    return scene;
}

void SceneFactory::loadSprites(lua_State *L, Scene *t_scene) {
    lua_getglobal(L, "sprites");
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {

        if (lua_istable(L, -1)) {
            lua_getfield(L, -1, "startPos");

            Sprite *sprite = new Sprite();
            if (lua_istable(L, -1)) {
                SDL_Rect startPos = SceneFactory::getRect(L, -1);
                std::cout << startPos.h << " " << startPos.w << " " << startPos.x << " " << startPos.y << std::endl;
                sprite->setStartPost(startPos);
            }

            lua_pop(L, 1);



            lua_getfield(L, -1, "startingAnimation");
            if (lua_isstring(L, -1)) {
                std::cout << "Setting initial sprite animation to " << lua_tostring(L, -1) << std::endl;
                sprite->setCurrentAnimation(lua_tostring(L, -1));
            }
            lua_pop(L, 1);

            // load sprite animations
            lua_getfield(L, -1, "animations");
            if (lua_istable(L, -1)) {
                lua_pushnil(L);
                while (lua_next(L, -2) != 0) {
                    // get name and clear lua stack
                    lua_getfield(L, -1, "name");
                    std::string animationName = lua_tostring(L, -1);
                    lua_pop(L, 1);

                    lua_getfield(L, -1, "textureId");
                    std::string textureId = lua_tostring(L, -1);
                    lua_pop(L, 1);

                    std::cout << "Adding animation '" << animationName << "' to sprite with textureId '" << textureId <<
                    "'" << std::endl;


                    // get animation sequences
                    std::vector<SDL_Rect> sequence;
                    // TODO optimization by counting sequences before and calling sequence.reserve(x)
                    lua_getfield(L, -1, "sequence");
                    if (lua_istable(L, -1)) {
                        lua_pushnil(L);
                        while (lua_next(L, -2) != 0) {
                            if (lua_istable(L, -1)) {
                                SDL_Rect rect = SceneFactory::getRect(L, -1);
                                std::cout << "\t frame => " << rect.x << " " << rect.y << " " << rect.h << " " <<
                                rect.w << std::endl;
                                sequence.push_back(rect);
                            }
                            lua_pop(L, 1);
                        }
                        lua_pop(L, 1);
                    }
                    lua_pop(L, 1);

                    sprite->addAnimations(animationName, new Animation(sequence, textureId));

                }
                lua_pop(L, 1);
            }
            t_scene->addSprite(sprite);
        }
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}




