#ifndef INC_2DGAME_SCENE_H
#define INC_2DGAME_SCENE_H

#include <list>
#include <vector>
#include "Sprite.h"

class Scene {
private:
    std::map<const std::string, SDL_Texture *> textures;
    SDL_Renderer *renderer;

public:
    std::vector<Sprite *> spriteList;

    Scene(SDL_Renderer *pRenderer);

    ~Scene();

    void draw();

    void notify(SDL_Event event);

    void addSprite(Sprite *sprite);

    void update(uint32_t time);

    void addTexture(const std::string name, SDL_Texture *texture);

    SDL_Renderer *getRenderer();
};


#endif //INC_2DGAME_SCENE_H
