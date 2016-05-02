#include "Config.h"
#include <iostream>

void Config::loadFromFile(std::string filename)  {
    lua_State * luaState = lua_open();

    if (luaL_loadfile(luaState, filename.c_str()) || lua_pcall(luaState, 0, 0, 0)) {
        std::cout << "cannot run configuration file:" << lua_tostring(luaState, -1) << std::endl;
    }

    lua_getglobal(luaState, "width");
    if (!lua_isnumber(luaState, -1)) {
        std::cout << "width should be a number" << std::endl;
    }
    width = (int) lua_tonumber(luaState, -1);

    lua_getglobal(luaState, "height");
    if (!lua_isnumber(luaState, -1)) {
        std::cout << "height should be a number" << std::endl;
    }
    height = (int) lua_tonumber(luaState, -1);

    lua_getglobal(luaState, "title");
    if (!lua_isstring(luaState, -1)) {
        std::cout << "title should be a string" << std::endl;
    }

    title = lua_tostring(luaState, -1);

    lua_getglobal(luaState, "startingScene");

    if (!lua_isstring(luaState, -1)) {
        std::cout << "startingScene should be a string" << std::endl;
    }

    startingScene = "../scripts/";
    startingScene += lua_tostring(luaState, -1);
    startingScene += ".lua";


}

