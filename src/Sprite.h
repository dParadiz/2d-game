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

    Sprite(SDL_Rect t_dstRect, SDL_Rect t_srcRect);

    SDL_Rect *getSrcRect();

    SDL_Rect *getPosition();

    void addAnimations(const std::string name, Animation *t_animations);

    const char * getTextureId();

    void update(uint32_t t_time);

    void setCurrentAnimation(const std::string &currentAnimation);

    void setStartPost(SDL_Rect rect);

private:
    SDL_Rect m_srcRect = {0, 0, 0, 0};
    SDL_Rect m_posRect = {0, 0, 0, 0};
    std::string m_currentAnimation;
    std::map<const std::string, std::shared_ptr<Animation>> m_animations;


};


#endif //INC_2DGAME_SPRITE_H
