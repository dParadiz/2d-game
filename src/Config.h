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

public:
    int width;
    int height;
    std::string title;
    std::string startingScene;
    void loadFromFile(std::string filename);

};


#endif //INC_2DGAME_CONFIG_H
