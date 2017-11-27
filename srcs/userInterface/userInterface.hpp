#ifndef __USER_INTERFACE_HPP
# define __USER_INTERFACE_HPP

#ifdef __cplusplus
extern "C" {
#endif
#include "SDL2/SDL.h"
#ifdef __cplusplus
}
#endif

#include <iostream>
#include "pool.hpp"

namespace mod1
{
class UserInterface
{
public:
    UserInterface(const std::shared_ptr<mod1::Pool> &pool,
                  int width,
                  int height);
    ~UserInterface();
    bool init();
    void start();

private:
//    Uint32 customEventCb(Uint32 interval, void *param);

    const std::shared_ptr<Pool> m_pool;
    SDL_Window *m_win = nullptr;
//    SDL_Surface *m_surface = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    int m_width;
    int m_height;
    bool m_ready = false;
};
}

#endif
