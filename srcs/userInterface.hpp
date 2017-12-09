
#ifndef __USER_INTERFACE_HPP
# define __USER_INTERFACE_HPP

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define WINDOW_SIZE (WINDOW_WIDTH * WINDOW_HEIGHT)
# define NB_FRAMES_PER_SECOND 25

#include <iostream>
#include <mod1.hpp>

#include "utils/pool.hpp"
#include "renderer/renderedFrame.hpp"
#include "physician/physicItems.hpp"

#include "overlay/sdlContext.hpp"
#include "overlay/fps.hpp"
#include "overlay/famine.hpp"
#include "overlay/idle.hpp"

namespace mod1
{
class UserInterface : public Fps, public Idle, public Famine
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
    bool m_ready = false;
    bool m_continueLoopHook = true;
};
}

#endif
