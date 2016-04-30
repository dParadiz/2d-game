#include <iostream>
#include "Scene.h"

void Scene::addSprite(Sprite *sprite) {
    m_spriteList.push_back(sprite);
}

void Scene::notify(SDL_Event event) {

    for (Sprite *sprite: m_spriteList) {
        sprite->notify(event);
    }
}

void Scene::draw(SDL_Renderer *renderer) {


    for (Sprite *sprite: m_spriteList) {
        SDL_Texture *texture = m_textures[sprite->getTextureId()];
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

        SDL_RenderCopy(renderer, texture, sprite->getSrcRect(), sprite->getPosition());
    }


}

void Scene::update(int t_time) {
    for (Sprite *sprite: m_spriteList) {
        sprite->update(t_time);
    }
}

void Scene::addTexture(const std::string name, SDL_Texture *t_texture) {
    std::cout << "Adding texture for " << name << std::endl;
    m_textures.insert(std::pair<const std::string, SDL_Texture*>(name, t_texture));
}

Scene::~Scene() {

    // clean up textures
    for (std::map<const std::string, SDL_Texture*>::iterator it=m_textures.begin(); it!=m_textures.end(); ++it) {
        if (it->second != nullptr) {
            std::cout << "Removing texture fir " << it->first << std::endl;
            SDL_DestroyTexture(it->second);
        }
    }

    m_textures.clear();
}

