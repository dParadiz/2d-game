//
// Created by dejan on 25.2.2016.
//
#include <iostream>
#include <stdexcept>

#include "SceneFactory.h"

void luaDump(lua_State *L) {
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {
        int t = lua_type(L, i);
        switch (t) {

            case LUA_TSTRING:
                std::cout << "String: " << lua_tostring(L, i) << std::endl;
                break;

            case LUA_TBOOLEAN:
                std::cout << "Bool: " << lua_toboolean(L, i) << std::endl;
                break;

            case LUA_TNUMBER:
                std::cout << "Number: " << lua_tonumber(L, i) << std::endl;
                break;
            case LUA_TTABLE:
                std::cout << "Table: " << std::endl;

                break;
            default:
                printf("%s", lua_typename(L, t));
                break;

        }

    }
}

void SceneFactory::processSprites(lua_State *L, int i) {
    if (!lua_istable(L, i)) {
        std::cout << "No table found on stack position " << i << std::endl;
        return;
    }

    std::cout << "Number of vars on stack " << lua_gettop(L) << std::endl;
    lua_pushnil(L);
    std::cout << "Number of vars on stack " << lua_gettop(L) << std::endl;
    std::string s;
    while (lua_next(L, i) != 0) {
        if (lua_istable(L, -1)) {

            lua_getfield(L, -1, "name");
            s = lua_tostring(L, -1);
            std::cout << "Sprite name " << s << std::endl;
            lua_pop(L, 1);
        }

        lua_pop(L, 1);
    }
    std::cout << "Sprite name " << s << std::endl;
    std::cout << "Number of vars on stack " << lua_gettop(L) << std::endl;
}

SDL_Rect getRect(lua_State *L) {
    int d[4] = {0, 0, 0, 0}, i = 0;
    if (lua_istable(L, -1)) {
        lua_pushnil(L);

        for( i = 0; i< 4;i++) {
            lua_next(L, -2);
            d[i] = (int) lua_tonumber(L, -1);
            lua_pop(L, 1);
        }

        lua_pop(L, 1);
    }
    return SDL_Rect{d[0], d[1], d[2], d[3]};
}

Scene *SceneFactory::createScene(SDL_Renderer *t_renderer, const char *sceneScript) {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    Scene *scene = new Scene;

    if (luaL_loadfile(L, sceneScript) || lua_pcall(L, 0, 0, 0)) {
        throw std::runtime_error(strcat((char *) "Error scene script: ", lua_tostring(L, -1)));
    } else {
        // load textures
        lua_getglobal(L, "textures");
        if (!lua_istable(L, -1)) {
            std::cout << "textures are not table " << std::endl;
        }

        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {

            if (lua_isstring(L, -1)) {
                std::cout << lua_tostring(L, -1) << std::endl;
                std::cout << lua_tostring(L, -2) << std::endl;
                SDL_Surface *image = SDL_LoadBMP(lua_tostring(L, -1));
                // TODO check if images can be loaded
                SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 105, 74, 46));
                scene->addTexture(lua_tostring(L, -2), SDL_CreateTextureFromSurface(t_renderer, image));
                SDL_FreeSurface(image);
            }

            lua_pop(L, 1);
        }
        lua_pop(L, 1);


        lua_getglobal(L, "sprites");
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {

            if (lua_istable(L, -1)) {
                lua_getfield(L, -1, "startPos");

                SDL_Rect rect = getRect(L);

                std::cout << rect.h << " " << rect.w << " " << rect.x << " " << rect.y << std::endl;
                lua_pop(L, 1);
            }

            lua_pop(L, 1);
        }
        lua_pop(L, 1);

        /*while (lua_next(L, -1) != 0) {
            if (lua_istable(L, -1)) {
            }

            lua_pop(L, 1);
        }*/
        //lua_getglobal(L, "name");

        //lua_getglobal(L, "background");

        //lua_getglobal(L, "sprites");

        //lua_getglobal(L, "resources");

        //SceneFactory::processSprites(L, 3);

    }
    lua_close(L);


    SDL_Surface *image = SDL_LoadBMP("../resources/spaceShip/main_sprite.bmp");
    SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 105, 74, 46));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(t_renderer, image);
    SDL_FreeSurface(image);
    Sprite *sprite = new Sprite({100, 100, 64, 29}, {0, 0, 64, 29});

    std::vector<SDL_Rect> flyAnimation;
    flyAnimation.reserve(4);
    flyAnimation.push_back(SDL_Rect{0, 0, 64, 29});
    flyAnimation.push_back(SDL_Rect{0, 29, 64, 29});
    flyAnimation.push_back(SDL_Rect{0, 58, 64, 29});
    flyAnimation.push_back(SDL_Rect{0, 87, 64, 29});


    sprite->addAnimations("fly", new Animation(flyAnimation));


    scene->m_spriteList.reserve(10);
    scene->addSprite(sprite);
    return scene;
}

