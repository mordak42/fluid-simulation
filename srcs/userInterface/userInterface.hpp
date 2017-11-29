#ifndef __USER_INTERFACE_HPP
# define __USER_INTERFACE_HPP

# define WINDOW_WIDTH 2000
# define WINDOW_HEIGHT 1000
# define WINDOW_SIZE (WINDOW_WIDTH * WINDOW_HEIGHT)

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
    void stop();

private:
    const std::shared_ptr<Pool> m_pool;
    SDL_Window *m_win = nullptr;
    SDL_Surface *m_surface = nullptr;
    bool m_ready = false;
    bool m_continueLoopHook = true;
    int m_width;
    int m_height;
};
}

#endif
