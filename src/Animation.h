#ifndef INC_2DGAME_ANIMATION_H
#define INC_2DGAME_ANIMATION_H


#include <functional>
#include <SDL_rect.h>
#include <vector>
#include <iostream>


class Animation {

public:

    Animation(const std::vector<SDL_Rect> &frames, const std::string &textureId);

    SDL_Rect getFrame(Uint32 time);

    const std::string &getTextureId() const;

    void setFps(int targetFps);

    size_t frame = 0;
private:
    std::vector<SDL_Rect> frames;
    Uint32 timeTick = 0;
    std::string textureId;
    int fps = 24;
};


#endif //INC_2DGAME_ANIMATION_H
