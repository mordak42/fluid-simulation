
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
#include <mod1.hpp>
#include "utils/pool.hpp"
#include "renderer/renderedFrame.hpp"
#include "physician/physicItems.hpp"

namespace mod1
{
class UserInterface
{
public:
    UserInterface(const std::shared_ptr<lib::Pool<RenderedFrame>> &pool,
                  int width,
                  int height);
    ~UserInterface();
    bool init();
    void start();
    void stop();

private:
    int Rgb_to_int(int r, int g, int b);
    const std::shared_ptr<lib::Pool<RenderedFrame>> &m_pool;
    SDL_Window *m_win = nullptr;
    SDL_Surface *m_surface = nullptr;
    bool m_ready = false;
    bool m_continueLoopHook = true;
    int m_width;
    int m_height;
};
}

#endif
