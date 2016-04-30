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

public:
    static Scene* createScene(SDL_Renderer *t_renderer, const char * t_sceneScript);

    static void processSprites(lua_State *L, int i);

    void processTable(lua_State *L, int i);
};


#endif //INC_2DGAME_SCENEFACTORY_H
