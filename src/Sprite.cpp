#include "Sprite.h"
#include <ctime>

void Sprite::notify(const Uint8 *state) {

    std::srand((unsigned int) std::time(0));

    if (state[SDL_SCANCODE_SPACE] && isAmmunition) {
        replicateAndMove = true;
    }


    if (!isEnemy && isControllable) {

        if (state[SDL_SCANCODE_LEFT]) {
            move(1);
        }

        if (state[SDL_SCANCODE_RIGHT]) {
            move(2);
        }

        if (state[SDL_SCANCODE_UP]) {
            //move(4);
        }

        if (state[SDL_SCANCODE_DOWN]) {
            //move(3);
        }

    }
}

void Sprite::move(const int direction) {
    if (direction == 1) {
        posRect.x -= 5;
    }

    if (direction == 2) {
        posRect.x += 5;
    }

    if (direction == 4) {
        posRect.y -= 5;
    }

    if (direction == 3 ) {
        posRect.y += 5;
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
        posRect.y -= 2;
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
    if (isEnemy) {

        if (time - replicatedAt > 50) { // enemy movement speed
            replicatedAt = time;
            move(std::rand() % 2 + 1);
            if (posRect.y > 600) { // screen height
                posRect.y = 0;
            }

            posRect.y += 1; // prefer down moment

            if (posRect.x < 0) {
                move(2);
            }

            if (posRect.x > 800 - 66) { // screen width sprite width
                posRect.x -= abs(posRect.x - 800 + 66);
                move(1);
            }
        }
    }

    if (isBullet) {
        move(4);
    }

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














