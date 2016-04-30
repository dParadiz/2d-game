#ifndef INC_2DGAME_SCENE_H
#define INC_2DGAME_SCENE_H

#include <list>
#include <vector>
#include "Sprite.h"

class Scene {
private:
    std::map<const std::string, SDL_Texture*> m_textures;
public:
    std::vector<Sprite *> m_spriteList;
    ~Scene();
    void draw(SDL_Renderer *renderer);

    void notify(SDL_Event event);

    void addSprite(Sprite *sprite);

    void update(int t_time);

    void addTexture(const std::string name, SDL_Texture *t_texture);
};


#endif //INC_2DGAME_SCENE_H
