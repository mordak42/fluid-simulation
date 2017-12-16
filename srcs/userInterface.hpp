
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
#include "overlay/displayer.hpp"
#include "overlay/bmp.hpp"

namespace mod1
{
class UserInterface : public Fps, public Idle, public Famine, public Displayer, public Bmp
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
    const std::shared_ptr<lib::Pool<RenderedFrame>> &m_pool;
    bool m_ready = false;
    bool m_continueLoopHook = true;
    float m_math_width = FRAME_WIDTH;
    float m_math_height = FRAME_HEIGHT;
    float m_deltaWidth = 1;
    float m_deltaHeight = 1;
    void displayNewFrame(RenderedFrame *img, bool oldStack);
    void keepSameFrame();
    enum uiState {
        notStarted = 0,
        firstFrameDisplayed,
        onPause,
        onStart,
        uiStatusMax
    };

    enum uiEvent {
        initialization = 0,
        plopEvent,
        switchWanted,
        nextFrameWanted,
        takePicture,
        uiEventMax
    };
    void finiteStateMachine(enum uiEvent evt);
    enum uiState m_uiState = notStarted;
};
}

#endif
