//
// Created by dejan on 26.2.2016.
//

#include "Config.h"
#include <iostream>

Config::Config(std::string filename) {
    m_luaState = lua_open();

    if (luaL_loadfile(m_luaState, filename.c_str()) || lua_pcall(m_luaState, 0, 0, 0)) {
        std::cout << "cannot run configuration file:" << lua_tostring(m_luaState, -1) << std::endl;
    }

    lua_getglobal(m_luaState, "width");
    if (!lua_isnumber(m_luaState, -1)) {
        std::cout << "width should be a number" << std::endl;
    }
    m_width = (int) lua_tonumber(m_luaState, -1);

    lua_getglobal(m_luaState, "height");
    if (!lua_isnumber(m_luaState, -1)) {
        std::cout << "height should be a number" << std::endl;
    }
    m_height = (int) lua_tonumber(m_luaState, -1);

    lua_getglobal(m_luaState, "title");
    if (!lua_isstring(m_luaState, -1)) {
        std::cout << "title should be a string" << std::endl;
    }

    m_title = lua_tostring(m_luaState, -1);

    lua_getglobal(m_luaState, "startingScene");

    if (!lua_isstring(m_luaState, -1)) {
        std::cout << "startingScene should be a string" << std::endl;
    }

    m_startingScene = "../scripts/";
    m_startingScene += lua_tostring(m_luaState, -1);
    m_startingScene += ".lua";


}

Config::~Config() {
    lua_close(m_luaState);
}
