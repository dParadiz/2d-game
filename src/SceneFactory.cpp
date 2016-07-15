#include <iostream>
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

SDL_Color SceneFactory::getColor(lua_State *L, int index) {
    Uint8 d[4] = {0, 0, 0, 0}, i = 0;
    if (lua_istable(L, index)) {
        lua_pushnil(L);

        for (i = 0; i < 4; i++) {
            lua_next(L, -2);
            d[i] = (Uint8) lua_tonumber(L, -1);
            lua_pop(L, 1);
        }

        lua_pop(L, 1);
    }
    SDL_Color color;
    color.r = d[0];
    color.g = d[1];
    color.b = d[2];
    color.a = d[3];
    return color;
}

void SceneFactory::loadTextures(lua_State *L, Scene *scene) {

    lua_getglobal(L, "transparentColor");
    SDL_Color tColor = SceneFactory::getColor(L, -1);
    lua_pop(L, 1);

    // load textures
    lua_getglobal(L, "textures");
    if (!lua_istable(L, -1)) {
        std::cout << "textures are not table " << std::endl;
        return;
    }

    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {

        if (lua_isstring(L, -1)) {
            SDL_Surface *image = SDL_LoadBMP(lua_tostring(L, -1));
            if (nullptr == image) {
                std::cout << "Could not load image: " << SDL_GetError() << std::endl;
            } else {
                SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, tColor.r, tColor.g, tColor.b));

                SDL_PixelFormat* pixelFormat = image->format;
                int bpp = pixelFormat->BytesPerPixel;

                std::vector<std::vector<int>> collisionMatrix((unsigned long) image->h, std::vector<int>(
                        (unsigned long) image->w, 0));;

                for(int x = 0; x < image->h;x++) {
                    for(int y = 0;  y < image->w;y++) {
                        Uint8* p = (Uint8*)image->pixels + x * image->pitch + y * bpp;
                        Uint8 red, green, blue, alpha;
                        SDL_GetRGBA(*p, pixelFormat, &red, &green, &blue, &alpha);

                        if (alpha == 255) {
                            collisionMatrix[x][y] = 1;
                        } else {
                            collisionMatrix[x][y] = 0;
                        }
                    }
                }


                scene->addTexture(lua_tostring(L, -2), SDL_CreateTextureFromSurface(scene->getRenderer(), image), collisionMatrix);

            }
            SDL_FreeSurface(image);
        }

        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}

Scene *SceneFactory::createScene(SDL_Renderer *renderer, const char *sceneScript) {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_loadfile(L, sceneScript) || lua_pcall(L, 0, 0, 0)) {
        throw std::runtime_error(strcat((char *) "Error scene script: ", lua_tostring(L, -1)));
    }

    SDL_RenderClear(renderer);
    Scene *scene = new Scene(renderer);

    SceneFactory::loadTextures(L, scene);
    // SceneFactory::loadAnimations(L, scene);
    SceneFactory::loadSprites(L, scene);

    return scene;
}

void SceneFactory::loadSprites(lua_State *L, Scene *scene) {
    lua_getglobal(L, "sprites");
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {

        if (lua_istable(L, -1)) {
            lua_getfield(L, -1, "startPos");

            Sprite *sprite = new Sprite();
            if (lua_istable(L, -1)) {
                SDL_Rect startPos = SceneFactory::getRect(L, -1);
                std::cout << "Starting position: " << startPos.h << " " << startPos.w << " " << startPos.x << " " <<
                startPos.y << std::endl;
                sprite->setStartPost(startPos);
            }

            lua_pop(L, 1);


            lua_getfield(L, -1, "startingAnimation");
            if (lua_isstring(L, -1)) {
                std::cout << "Setting initial sprite animation to " << lua_tostring(L, -1) << std::endl;
                sprite->setCurrentAnimation(lua_tostring(L, -1));
            }
            lua_pop(L, 1);

            lua_getfield(L, -1, "controllable");
            if (lua_isboolean(L, -1)) {
                std::cout << "Setting controllable flag for the sprite"<< std::endl;
                sprite->isControllable = (bool)lua_toboolean(L, -1);
            }
            lua_pop(L, 1);

            lua_getfield(L, -1, "hidden");
            if (lua_isboolean(L, -1)) {
                std::cout << "Setting visible flag for the sprite"<< std::endl;
                sprite->isVisible =  !(bool)lua_toboolean(L, -1);
            }
            lua_pop(L, 1);

            lua_getfield(L, -1, "ammunition");
            if (lua_isboolean(L, -1)) {
                std::cout << "Setting bullet flag for the sprite"<< std::endl;
                sprite->isAmmunition =  (bool)lua_toboolean(L, -1);
            }
            lua_pop(L, 1);


            lua_getfield(L, -1, "enemyAI");
            if (lua_isboolean(L, -1)) {
                std::cout << "Setting enemyAI flag for the sprite"<< std::endl;
                sprite->isEnemy =  (bool)lua_toboolean(L, -1);
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

                    int fps = 0;
                    lua_getfield(L, -1, "fps");
                    if (lua_isnumber(L, -1)) {
                        std::cout << "Setting fps rate for animation" << std::endl;
                        fps = (int) lua_tonumber(L, -1);
                    }
                    lua_pop(L, 1);

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


                    Animation * animation = new Animation(sequence, textureId);
                    animation->setFps(fps);

                    sprite->addAnimation(animationName, animation);

                }
                lua_pop(L, 1);
            }
            scene->addSprite(sprite);
        }
        lua_pop(L, 1);


    }
    lua_pop(L, 1);
}




