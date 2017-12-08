
#ifndef __FPS_HPP__
# define __FPS_HPP__

#ifdef __cplusplus
extern "C" {
#endif
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#ifdef __cplusplus
}
#endif

#include <iostream>
#include <chrono>

namespace mod1
{
class Fps
{
public:
    Fps();
    ~Fps();
    int init();
    void setTimeOrigin();
    void updateFpsCounter();
    void updateIddleField();
    void fillInformations(SDL_Surface *screen, bool enableDisplaying);

private:
    TTF_Font *m_font = nullptr;
    bool m_ready = false;
    std::chrono::high_resolution_clock::time_point m_originTime;
    int m_nbFrames = 0;
};
}

#endif
