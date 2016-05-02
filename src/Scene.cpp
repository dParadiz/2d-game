#include <iostream>
#include "Scene.h"

void Scene::addSprite(Sprite *sprite) {
    spriteList.push_back(sprite);
}

void Scene::notify(SDL_Event event) {

    for (Sprite *sprite: spriteList) {
        sprite->notify(event);
    }
}

void Scene::draw() {

    SDL_RenderClear(renderer);

    for (Sprite *sprite: spriteList) {
        SDL_Texture *texture = textures[sprite->getTextureId()];
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderer, texture, sprite->getSrcRect(), sprite->getPosition());
    }

    SDL_RenderPresent(renderer);
}

void Scene::update(uint32_t time) {
    for (Sprite *sprite: spriteList) {
        sprite->update(time);
    }
}

void Scene::addTexture(const std::string name, SDL_Texture *texture) {
    std::cout << "Adding texture " << name << " to scene" << std::endl;
    textures.insert(std::pair<const std::string, SDL_Texture *>(name, texture));
}

Scene::~Scene() {

    // clean up textures
    for (std::map<const std::string, SDL_Texture *>::iterator it = textures.begin(); it != textures.end(); ++it) {
        if (it->second != nullptr) {
            std::cout << "Destroying texture " << it->first << std::endl;
            SDL_DestroyTexture(it->second);
        }
    }

    textures.clear();


}

Scene::Scene(SDL_Renderer *t_renderer) : renderer(t_renderer) { }

SDL_Renderer *Scene::getRenderer() {
    return renderer;
}









