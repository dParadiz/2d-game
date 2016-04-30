//
// Created by dejan on 10.1.2016.
//

#ifndef INC_2DGAME_ANIMATION_H
#define INC_2DGAME_ANIMATION_H


#include <functional>
#include <SDL_rect.h>
#include <vector>

typedef std::function<SDL_Rect(SDL_Rect srcRect, int time)> Sequence;

class Animation {

public:

    Animation(const std::vector<SDL_Rect> &t_frames);

    SDL_Rect getFrame(Uint32 t_time);
    void setFps(int t_fps);
//    void start();
//    void stop();
//    bool isPlaying();
    size_t m_frame = 0;
private:
    std::vector<SDL_Rect> m_frames;
    Uint32 m_timeTick = 0;
    int m_fps = 24;
};


#endif //INC_2DGAME_ANIMATION_H
