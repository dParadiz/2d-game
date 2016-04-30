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

    Sprite(SDL_Rect startPos);

    Sprite(SDL_Rect t_dstRect, SDL_Rect t_srcRect);

    SDL_Rect *getSrcRect();

    SDL_Rect *getPosition();

    void addAnimations(const std::string name, Animation *t_animations);

    const char * getTextureId();

    void update(int t_time);

private:
    SDL_Rect srcRect;
    SDL_Rect posRect;
    std::map<const std::string, std::shared_ptr<Animation>> m_animations;


};


#endif //INC_2DGAME_SPRITE_H
