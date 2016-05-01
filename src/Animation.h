//
// Created by dejan on 10.1.2016.
//

#ifndef INC_2DGAME_ANIMATION_H
#define INC_2DGAME_ANIMATION_H


#include <functional>
#include <SDL_rect.h>
#include <vector>
#include <iostream>



class Animation {

public:

    Animation(const std::vector<SDL_Rect> &t_frames, const std::string &t_textureId);

    SDL_Rect getFrame(Uint32 t_time);

    const std::string &getTextureId() const;

    void setFps(int t_fps);

    size_t m_frame = 0;
private:
    std::vector<SDL_Rect> m_frames;
    Uint32 m_timeTick = 0;
    std::string m_textureId;
    int m_fps = 24;
};


#endif //INC_2DGAME_ANIMATION_H
