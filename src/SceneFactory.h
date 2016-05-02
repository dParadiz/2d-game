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

    static void loadSprites(lua_State *pState, Scene *scene);

    static void loadTextures(lua_State *L, Scene *scene);

    static SDL_Color getColor(lua_State *L, int index);

public:
    static Scene *createScene(SDL_Renderer *renderer, const char *sceneScript);


};


#endif //INC_2DGAME_SCENEFACTORY_H
