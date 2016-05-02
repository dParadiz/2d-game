#include "Animation.h"


Animation::Animation(const std::vector<SDL_Rect> &frames, const std::string &textureId)
        : frames(frames),
          textureId(textureId) {

}

SDL_Rect Animation::getFrame(Uint32 time) {

    if (timeTick != fps * time / 1000) {
        ++frame;
        timeTick = fps * time / 1000;
    }
    // loop
    if (frame >= frames.size()) {
        frame = 0;
    }

    return frames.at(frame);
}


void Animation::setFps(int targetFps) {
    fps = 1000 / targetFps;
}

const std::string &Animation::getTextureId() const {
    return textureId;
}


