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

void Scene::draw() {

    SDL_RenderClear(m_renderer);

    for (Sprite *sprite: m_spriteList) {
        SDL_Texture *texture = m_textures[sprite->getTextureId()];
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(m_renderer, texture, sprite->getSrcRect(), sprite->getPosition());
    }

    SDL_RenderPresent(m_renderer);
}

void Scene::update(uint32_t t_time) {
    for (Sprite *sprite: m_spriteList) {
        sprite->update(t_time);
    }
}

void Scene::addTexture(const std::string name, SDL_Texture *t_texture) {
    std::cout << "Adding texture " << name << " to scene" << std::endl;
    m_textures.insert(std::pair<const std::string, SDL_Texture *>(name, t_texture));
}

Scene::~Scene() {

    // clean up textures
    for (std::map<const std::string, SDL_Texture *>::iterator it = m_textures.begin(); it != m_textures.end(); ++it) {
        if (it->second != nullptr) {
            std::cout << "Destroying texture " << it->first << std::endl;
            SDL_DestroyTexture(it->second);
        }
    }

    m_textures.clear();


}

Scene::Scene(SDL_Renderer *t_renderer) : m_renderer(t_renderer) { }

SDL_Renderer *Scene::getRenderer() {
    return m_renderer;
}









