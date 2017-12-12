
#ifndef __USER_INTERFACE_HPP
# define __USER_INTERFACE_HPP

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
enum uiState {
    notStarted = 0,
    firstFrameDisplayed,
    onPause,
    onResizePaused,
    onStart,
    uiStatusMax
};

enum uiEvent {
    initialization = 0,
    frameAvailable,
    frameDisplayed,
    startedWanted,
    stoppedWanted,
    resizeWanted,
    uiEventMax
};

public:
    UserInterface(const std::shared_ptr<lib::Pool<RenderedFrame>> &pool,
                  int width,
                  int height);
    ~UserInterface();
    bool init();
    void start();
    void stop();

private:
    void fillNewsurface();
    void keepSameSurface();

    int Rgb_to_int(int r, int g, int b);
    const std::shared_ptr<lib::Pool<RenderedFrame>> &m_pool;
    bool m_ready = false;
    bool m_continueLoopHook = true;
    float m_math_width = FRAME_WIDTH;
    float m_math_height = FRAME_HEIGHT;
    float m_deltaWidth;
    float m_deltaHeight;

    RenderedFrame *m_img = NULL;
    void finiteStateMachine(enum uiEvent evt);
    enum uiState m_uiState = notStarted;

};
}

#endif
