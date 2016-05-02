#ifndef INC_2DGAME_SPRITE_H
#define INC_2DGAME_SPRITE_H

#include <SDL2/SDL.h>
#include <string>
#include <functional>
#include <map>
#include <queue>
#include "Animation.h"
#include <memory>

class Sprite {

public:
    void notify(SDL_Event event);

    Sprite();
    Sprite(SDL_Rect startPos);

    Sprite(SDL_Rect dstRect, SDL_Rect srcRect);

    SDL_Rect *getSrcRect();

    SDL_Rect *getPosition();

    void addAnimation(const std::string name, Animation *animation);

    const char * getTextureId();

    void update(uint32_t time);

    void setCurrentAnimation(const std::string &currentAnimation);

    void setStartPost(SDL_Rect rect);

private:
    SDL_Rect srcRect = {0, 0, 0, 0};
    SDL_Rect posRect = {0, 0, 0, 0};
    std::string currentAnimation;
    std::map<const std::string, std::shared_ptr<Animation>> animations;


};


#endif //INC_2DGAME_SPRITE_H
