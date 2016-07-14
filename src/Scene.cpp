#include <iostream>
#include <algorithm>
#include "Scene.h"


const int GRID_W = 80;
const int GRID_H  = 80;

void Scene::addSprite(Sprite *sprite) {
    spriteList.push_back(sprite);
}

void Scene::notify(const Uint8 *state) {

    for (Sprite *sprite: spriteList) {
        sprite->notify(state);
    }
}

void Scene::draw() {

    SDL_RenderClear(renderer);

    for (Sprite *sprite: spriteList) {

        if (!sprite->isVisible) {
            continue;
        }

        SDL_Texture *texture = textures[sprite->getTextureId()];
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderer, texture, sprite->getSrcRect(), sprite->getPosition());
    }

    //grid
    /*for(int i = 0; i < 10; i++) {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderDrawLine(renderer, i* GRID_W, 0, i * GRID_W, 600);
    }

    for(int i = 0; i < 10; i++) {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderDrawLine(renderer, 0, i*GRID_H, 800, i*GRID_H);
    }*/

    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderPresent(renderer);
}

void Scene::update(uint32_t time) {
    std::vector<Sprite *> v;

    for (Sprite *sprite: spriteList) {

        if (sprite->replicateAndMove && (time - sprite->replicatedAt) > 1000) { // shooting speed
            sprite->replicatedAt = time;
            Sprite *spriteReplica = sprite->clone();
            spriteReplica->isControllable = false;
            spriteReplica->replicateAndMove = false;
            spriteReplica->isBullet = true;
            spriteReplica->isVisible = true;

            v.push_back(spriteReplica);
        }

        sprite->replicateAndMove = false;

        sprite->update(time);
        //clean up sprites
        if (sprite->getPosition()->y < 0) {
            sprite->canBeRemoved = true;
        }

    }

    // check for collision
    // get sprites in same grid space
    int gridW = GRID_W;
    int gridH = GRID_H;

    std::map<const std::string, std::vector<Sprite *>> collisionMap;

    for (Sprite *sprite: spriteList) {
        SDL_Rect *rect = sprite->getPosition();
        int posX = rect->x / gridW;
        int posW = (rect->x + rect->w) / gridW;
        int posY = rect->y / gridH;
        int posH = (rect->y + rect->h) / gridH;

        // collision only for bullets and enemies
        if (!(sprite->isBullet || sprite->isEnemy)) {
            continue;
        }

        std::string cord;
        // grid tile must be big enough, not to split spites in more then 4 pieces
        cord = std::to_string(posX) + "_" + std::to_string(posY);

        if (collisionMap.find(cord) != collisionMap.end()) {
            std::vector<Sprite *> spriteList;
            collisionMap.insert(std::pair<const std::string, std::vector<Sprite *>>(cord, spriteList));
        }
        collisionMap[cord].push_back(sprite);

        if (cord != std::to_string(posW) + "_" + std::to_string(posY)) {
            cord = std::to_string(posW) + "_" + std::to_string(posY);

            if (collisionMap.find(cord) != collisionMap.end()) {
                std::vector<Sprite *> spriteList;
                collisionMap.insert(std::pair<const std::string, std::vector<Sprite *>>(cord, spriteList));
            }
            collisionMap[cord].push_back(sprite);
        }

        if (cord != std::to_string(posX) + "_" + std::to_string(posH)) {
            cord = std::to_string(posX) + "_" + std::to_string(posH);
            if (collisionMap.find(cord) != collisionMap.end()) {
                std::vector<Sprite *> spriteList;
                collisionMap.insert(std::pair<const std::string, std::vector<Sprite *>>(cord, spriteList));
            }
            collisionMap[cord].push_back(sprite);
        }

        if (cord != std::to_string(posW) + "_" + std::to_string(posH)) {
            cord = std::to_string(posW) + "_" + std::to_string(posH);

            if (collisionMap.find(cord) != collisionMap.end()) {
                std::vector<Sprite *> spriteList;
                collisionMap.insert(std::pair<const std::string, std::vector<Sprite *>>(cord, spriteList));
            }
            collisionMap[cord].push_back(sprite);
        }

    }

    for (auto &iter: collisionMap) {
        if (iter.second.capacity() > 1) {
            Sprite *sSprite;
            sSprite = iter.second.back();
            iter.second.pop_back();

            if (!sSprite->canBeRemoved) {
                for (Sprite *sprite:iter.second) {

                    if (sprite->canBeRemoved  // already removed no collision needed
                        || sSprite->isEnemy && sprite->isEnemy // enemies don't collied between them self
                        || sSprite->isBullet && sprite->isBullet // bullets don't collied between them self
                            ) {
                        continue;
                    }

                    if (SDL_HasIntersection(sprite->getPosition(), sSprite->getPosition())) {

                        sSprite->canBeRemoved = true;
                        sprite->canBeRemoved = true;
                    }
                }
            }
        }

    }

    auto canBeRemoved = [](Sprite *sprite) { return sprite->canBeRemoved; };
    spriteList.erase(std::remove_if(spriteList.begin(), spriteList.end(), canBeRemoved), spriteList.end());
    spriteList.insert(spriteList.end(), v.begin(), v.end());
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









