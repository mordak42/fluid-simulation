
#ifndef __SDL_CONTEXT_HPP__
# define __SDL_CONTEXT_HPP__

#ifdef __cplusplus
extern "C" {
#endif
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#ifdef __cplusplus
}
#endif

#include <iostream>

namespace mod1
{
class SdlContext
{
public:
    SdlContext();
    SdlContext(std::string & windowName);
    SdlContext(int width, int height);
    SdlContext(int width, int height, std::string & windowName);
    SdlContext(int width, int height, int posX, int posY, std::string & windowName);
    ~SdlContext();

protected:
    SDL_Window *m_win = nullptr;
    SDL_Surface *m_surface = nullptr;
    int m_width = 1920;
    int m_height = 1080;

    /* Debug tool, usual for diamond heartens behavior test */
    void updateRefCount();
    int getRefCount();

private:
    bool init();

    std::string m_windowName = "SdlContext";
    int m_posX = SDL_WINDOWPOS_CENTERED;
    int m_posY = SDL_WINDOWPOS_CENTERED;

    int m_refCount = 0;
};
}

#endif
