#include "Sprite.h"

void Sprite::notify(SDL_Event event) {

    if (posRect.x == 0 && posRect.y == 0 && posRect.h == 0 && posRect.w == 0) {
        return;
    }

    switch (event.key.keysym.sym) {
        case SDLK_UP:
            posRect.y -= 16;
            break;
        case SDLK_DOWN:
            posRect.y += 16;
            break;
        case SDLK_RIGHT:
            posRect.x += 16;
            break;
        case SDLK_LEFT:
            posRect.x -= 16;
            break;
        case SDLK_SPACE:
            //animationQueue.push("fly");
            break;
        default:
            break;
    }
}

SDL_Rect *Sprite::getSrcRect() {

    if (srcRect.x == 0 && srcRect.y == 0 && srcRect.h == 0 && srcRect.w == 0) {
        return NULL;
    }

    return &srcRect;
}

SDL_Rect *Sprite::getPosition() {
    if (posRect.x == 0 && posRect.y == 0 && posRect.h == 0 && posRect.w == 0) {
        return NULL;
    }
    return &posRect;
}


Sprite::Sprite(SDL_Rect startPos) : posRect(startPos) {

}

Sprite::Sprite(SDL_Rect dstRect, SDL_Rect srcRect) : posRect(dstRect), srcRect(srcRect) {

}

void Sprite::addAnimation(const std::string name, Animation *animation) {
    std::shared_ptr<Animation> animationPtr(animation);
    animations.insert(std::pair<const std::string, std::shared_ptr<Animation>>(name, animationPtr));
}

void Sprite::update(uint32_t time) {
    Animation *animation = animations[currentAnimation].get();

    srcRect = animation->getFrame(time);

}

const char *Sprite::getTextureId() {

    return animations[currentAnimation]->getTextureId().c_str();
}

void Sprite::setCurrentAnimation(const std::string &animation) {
    currentAnimation = animation;
}

Sprite::Sprite() { }

void Sprite::setStartPost(SDL_Rect rect) {
    posRect = rect;
}












