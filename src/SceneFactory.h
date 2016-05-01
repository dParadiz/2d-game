//
// Created by dejan on 25.2.2016.
//

#ifndef INC_2DGAME_SCENEFACTORY_H
#define INC_2DGAME_SCENEFACTORY_H

#include "Scene.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}


class SceneFactory {

private:
    static SDL_Rect getRect(lua_State *L, int index);
    static void loadSprites(lua_State *pState, Scene *t_Scene);
    static void loadTextures(lua_State *L, Scene *t_scene);
    static SDL_Color getColor(lua_State *L, int index);

public:
    static Scene *createScene(SDL_Renderer *t_renderer, const char *t_sceneScript);


};


#endif //INC_2DGAME_SCENEFACTORY_H
