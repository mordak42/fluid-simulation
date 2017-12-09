
#ifndef __FPS_HPP__
# define __FPS_HPP__

#define MAX_FPS_NUMBER 100
#define PADDING_FPS 10

#include <iostream>

#include "overlay/sdlContext.hpp"

namespace mod1
{
class Fps : public virtual SdlContext
{

public:
    Fps();
    ~Fps();
    int fpsMeterInit();
    void setTimeOrigin();
    void updateFpsCounter();
    void updateFpsField();

private:
    TTF_Font *m_font = nullptr;
    SDL_Surface *m_font_surface[MAX_FPS_NUMBER] = {0};
    std::chrono::high_resolution_clock::time_point m_originTime;
    int m_nbFrames = 0;
    int m_savedFps = -1;
    bool m_ready = false;
};
}

#endif
