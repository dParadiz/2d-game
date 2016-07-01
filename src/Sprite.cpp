#include "Sprite.h"

void Sprite::notify(SDL_Event event) {

    if (!isControllable) {
        return;
    }

    switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            if (event.type == SDL_KEYDOWN) {
                posRect.x -= 20;
            }
            break;
        case SDLK_RIGHT:
            if (event.type == SDL_KEYDOWN) {
                posRect.x += 20;
            }
            break;
        case SDLK_UP:
            if (event.type == SDL_KEYDOWN) {
                posRect.y -= 20;
            }
            break;
        case SDLK_DOWN:
            if (event.type == SDL_KEYDOWN) {
                posRect.y += 20;
            }
            break;
        case SDLK_SPACE:
            if (isBullet && event.type == SDL_KEYUP) {
                replicateAndMove = true;
            }
            break;
        default:
            return;
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

    if (isBullet && isClone) {
        posRect.y -= 10;
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

Sprite *Sprite::clone() {

    Sprite *sprite = new Sprite(this->posRect, this->srcRect);
    sprite->isBullet = isBullet;
    sprite->currentAnimation = currentAnimation;
    sprite->animations = animations;
    sprite->isControllable = isControllable;
    sprite->isVisible = isVisible;
    sprite->isClone = true;

    return sprite;
}














