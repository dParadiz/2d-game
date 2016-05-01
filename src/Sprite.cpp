#include "Sprite.h"

void Sprite::notify(SDL_Event event) {

    if (m_posRect.x == 0 && m_posRect.y == 0 && m_posRect.h == 0 && m_posRect.w == 0) {
        return;
    }

    switch (event.key.keysym.sym) {
        case SDLK_UP:
            m_posRect.y -= 16;
            break;
        case SDLK_DOWN:
            m_posRect.y += 16;
            break;
        case SDLK_RIGHT:
            m_posRect.x += 16;
            break;
        case SDLK_LEFT:
            m_posRect.x -= 16;
            break;
        case SDLK_SPACE:
            //animationQueue.push("fly");
            break;
        default:
            break;
    }
}

SDL_Rect *Sprite::getSrcRect() {

    if (m_srcRect.x == 0 && m_srcRect.y == 0 && m_srcRect.h == 0 && m_srcRect.w == 0) {
        return NULL;
    }

    return &m_srcRect;
}

SDL_Rect *Sprite::getPosition() {
    if (m_posRect.x == 0 && m_posRect.y == 0 && m_posRect.h == 0 && m_posRect.w == 0) {
        return NULL;
    }
    return &m_posRect;
}


Sprite::Sprite(SDL_Rect startPos) : m_posRect(startPos) {

}

Sprite::Sprite(SDL_Rect t_dstRect, SDL_Rect t_srcRect) : m_posRect(t_dstRect), m_srcRect(t_srcRect) {

}

void Sprite::addAnimations(const std::string name, Animation *t_animation) {
    std::shared_ptr<Animation> animation(t_animation);
    m_animations.insert(std::pair<const std::string, std::shared_ptr<Animation>>(name, animation));
}

void Sprite::update(uint32_t t_time) {
    Animation *animation = m_animations[m_currentAnimation].get();

    m_srcRect = animation->getFrame(t_time);

}

const char *Sprite::getTextureId() {

    return m_animations[m_currentAnimation]->getTextureId().c_str();
}

void Sprite::setCurrentAnimation(const std::string &currentAnimation) {
    m_currentAnimation = currentAnimation;
}

Sprite::Sprite() { }

void Sprite::setStartPost(SDL_Rect rect) {
    m_posRect = rect;
}












