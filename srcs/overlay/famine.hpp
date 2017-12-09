
#ifndef __FAMINE_HPP__
# define __FAMINE_HPP__

#define PADDING_FAMINE 10

#include "overlay/sdlContext.hpp"

namespace mod1
{
class Famine : public virtual SdlContext
{

public:
    Famine();
    ~Famine();

protected:
    bool initFamine();
    void setFamine();
    void updateFamineField();

private:
    TTF_Font *m_font = nullptr;
    SDL_Surface *m_font_surface = nullptr;
    bool m_onStarvation = false;
    std::chrono::high_resolution_clock::time_point m_originTime;
    bool m_ready = false;
};
}

#endif
