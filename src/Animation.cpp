//
// Created by dejan on 10.1.2016.
//

#include "Animation.h"


Animation::Animation(const std::vector<SDL_Rect> &t_frames, const std::string &t_textureId)
        : m_frames(t_frames),
          m_textureId(t_textureId) {

}


/*void Animation::start() {
    m_playing = true;
}

void Animation::stop() {
    m_playing = false;
}
bool Animation::isPlaying() {
    return m_playing;
}
 */
SDL_Rect Animation::getFrame(Uint32 t_time) {

    if (m_timeTick != m_fps * t_time / 1000) {
        ++m_frame;
        m_timeTick = m_fps * t_time / 1000;
    }
    // loop
    if (m_frame >= m_frames.size()) {
        m_frame = 0;
    }

    return m_frames.at(m_frame);
}


void Animation::setFps(int t_fps) {
    m_fps = 1000 / t_fps;
}

const std::string &Animation::getTextureId() const {
    return m_textureId;
}


