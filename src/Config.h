//
// Created by dejan on 26.2.2016.
//

#ifndef INC_2DGAME_CONFIG_H
#define INC_2DGAME_CONFIG_H

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#ifndef lua_open
#define lua_open luaL_newstate
#endif

#include <string>

class Config {
private:
    lua_State *m_luaState;
public:
    int m_width;
    int m_height;
    std::string m_title;
    std::string m_startingScene;

    Config(std::string filename);

    ~Config();
};


#endif //INC_2DGAME_CONFIG_H
