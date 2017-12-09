
#ifndef __IDLE_HPP__
# define __IDLE_HPP__

#define MAX_IDLE_NUMBER 100
#define PADDING_IDLE_X 150
#define PADDING_IDLE_Y 10

#include <iostream>

#include "overlay/sdlContext.hpp"

namespace mod1
{
class Idle : public virtual SdlContext
{

public:
    Idle(int nbFrames);
    ~Idle();
    int IdleMeterInit();
    void setIdleStartPoint();
    void updateIdleField();
    void determineIdle();

private:
    TTF_Font *m_font = nullptr;
    SDL_Surface *m_font_surface[MAX_IDLE_NUMBER] = {0};
    std::chrono::high_resolution_clock::time_point m_originTime;
    int m_savedIdle = -1;
    int m_nbFrames = 25;
    bool m_ready = false;
    int m_count = 0;
};
}

#endif
