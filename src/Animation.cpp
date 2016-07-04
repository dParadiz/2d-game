#include "Animation.h"


Animation::Animation(const std::vector<SDL_Rect> &frames, const std::string &textureId)
        : frames(frames),
          textureId(textureId) {

}

SDL_Rect Animation::getFrame(Uint32 time) {

    if (fps == 0) {
        return frames.at(0);
    }

    if (time - timeTick > fps) {
        ++frame;
        timeTick = time;
    }

    // loop
    if (frame >= frames.size()) {
        frame = 0;
    }

    return frames.at(frame);
}


void Animation::setFps(int targetFps) {

    if (targetFps < 1) {
        fps = 0;
        return;
    }

    fps = 1000 / targetFps;
}

const std::string &Animation::getTextureId() const {
    return textureId;
}


