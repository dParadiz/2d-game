#ifndef INC_2DGAME_SCENE_H
#define INC_2DGAME_SCENE_H

#include <list>
#include <vector>
#include "Sprite.h"

class Scene {
private:
    std::map<const std::string, SDL_Texture*> m_textures;
    SDL_Renderer *m_renderer;

public:
    std::vector<Sprite *> m_spriteList;
    Scene(SDL_Renderer *pRenderer);
    ~Scene();
    void draw();

    void notify(SDL_Event event);

    void addSprite(Sprite *sprite);

    void update(uint32_t t_time);

    void addTexture(const std::string name, SDL_Texture *t_texture);

    SDL_Renderer *getRenderer();
};


#endif //INC_2DGAME_SCENE_H
