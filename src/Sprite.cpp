#include "Sprite.h"

void Sprite::notify(SDL_Event event) {


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
    return &srcRect;
}

SDL_Rect *Sprite::getPosition() {
    return &posRect;
}


Sprite::Sprite(SDL_Rect startPos) : posRect(startPos) {

}

Sprite::Sprite(SDL_Rect t_dstRect, SDL_Rect t_srcRect) :  posRect(t_dstRect), srcRect(t_srcRect) {

}

void Sprite::addAnimations(const std::string name, Animation *t_animation) {
    std::shared_ptr<Animation> animation(t_animation);
    m_animations.insert(std::pair<const std::string, std::shared_ptr<Animation>>(name, animation));
}

void Sprite::update(int t_time) {

    //if (animationQueue.empty()) {
    // endless loop by default
    Animation *animation = m_animations["fly"].get();
    //if ((t_time / 100) == 0) {

    SDL_Rect frameRect = animation->getFrame(t_time);
    srcRect.x = frameRect.x;
    srcRect.y = frameRect.y;
    srcRect.w = frameRect.w;
    srcRect.h = frameRect.h;

    //printf("%d %d %d %d\n", srcRect.x, srcRect.y, srcRect.w, srcRect.h);
    //}
    //printf("Frame %d\n", animation.m_frame);
    // animation has ended so we remove it form the queue

    //}
}

const char *Sprite::getTextureId() {
    return "main";
}






