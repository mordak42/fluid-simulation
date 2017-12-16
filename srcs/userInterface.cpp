
#include "userInterface.hpp"

using namespace mod1;

UserInterface::UserInterface(const std::shared_ptr<lib::Pool<RenderedFrame>> &pool,
                             int width,
                             int height) :
                                SdlContext(width, height),
                                Fps(),
                                Idle(NB_FRAMES_PER_SECOND),
                                Famine(),
                                Displayer(),
                                m_pool(pool)
{
    /* Debug test */
    updateRefCount();
}

UserInterface::~UserInterface() {}

bool UserInterface::init() {
    if (m_ready == true) {
        std::cerr << __func__ << " : SDL2 already initialized" << std::endl;
        return false;
    }

    m_surface = SDL_GetWindowSurface(m_win);
    m_ready = true;

    if (initFamine() == false)
        std::cerr << "Cannot initialize Famine" << std::endl;
    if (fpsMeterInit() == false)
        std::cerr << "Cannot initialize FPS meter" << std::endl;
    if (IdleMeterInit() == false)
        std::cerr << "Cannot initialize Idle meter" << std::endl;
    if (initFont("srcs/fonts/Chalkduster.ttf", 25) == false)
        std::cerr << "Cannot initialize Displayer" << std::endl;

    /* Debug test */
    std::cout << "Actual parent refCount is " << getRefCount() << "/5" << std::endl;
    return true;
}
static Uint32 customEventCb(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userEvent;

    /* In this example, our callback pushes a function
    into the queue, and causes our callback to be called again at the
    same interval: */

    userEvent.type = SDL_USEREVENT;
    userEvent.code = 0;
    userEvent.data1 = NULL;
    userEvent.data2 = param;


    event.type = SDL_USEREVENT;
    event.user = userEvent;

    SDL_PushEvent(&event);
    return(interval);
}

void UserInterface::displayNewFrame(RenderedFrame *img, bool oldStack) {
 //   std::cout << "resolutionTime for this frame = " << (int)(img->solvedTime * 1000) << " ms" << std::endl;
    setIdleStartPoint();
    updateFpsCounter();
    int h = m_width;
    for (int y = 0; y < m_height; y++) {
        double j = (int)(m_deltaHeight * y) * m_math_width;
        for (int i = h - m_width; i < h; i++) {
            ((int *)m_surface->pixels)[i] = ((int *)img->m_map)[(int)(j)];
            j += m_deltaWidth;
        }
        h += m_width;
    }
    if (oldStack == false)
        m_pool->pushOutdatedItem(img);
    updateFamineField();
    updateFpsField();
    updateIdleField();
    displayMsg(0, 9999, 0x00FFFF00, "%i ms", (int)(img->solvedTime * 1000));
    SDL_UpdateWindowSurface(m_win);
    determineIdle();
}

void UserInterface::keepSameFrame() {
    setFamine();
    updateFamineField();
    updateFpsField();
    updateIdleField();
    SDL_UpdateWindowSurface(m_win);
}

void UserInterface::finiteStateMachine(enum uiEvent evt) {
    RenderedFrame *img;

    switch (m_uiState) {
    case notStarted:
        switch (evt) {
        case initialization:
            m_uiState = firstFrameDisplayed;
            break;
        default:
            std::cerr << "FSM cannot process event while not initialized" << std::endl;
            break;
        }
        break;
    case firstFrameDisplayed:
        switch (evt) {
        case plopEvent:
            img = m_pool->popRenderedItem();
            if (img == NULL) {
                std::cerr << "NULL image exception !" << std::endl;
                return;
            }
            displayNewFrame(img, false);
            m_uiState = onPause;
            break;
        default:
            break;
        }
        break;
    case onPause:
        switch (evt) {
        case switchWanted:
            setTimeOrigin();
            m_uiState = onStart;
            break;
        case plopEvent:
             img = m_pool->getLastRenderedFrame();
            if (img)
                displayNewFrame(img, true);
            else
                keepSameFrame();
            break;
        case nextFrameWanted:
            img = m_pool->popRenderedItem();
            if (img)
                displayNewFrame(img, false);
            else
                keepSameFrame();
            break;
        default:
            break;
        }
        break;
    case onStart:
        switch (evt) {
        case switchWanted:
            m_uiState = onPause;
            break;
        case plopEvent:
            img = m_pool->popRenderedItem();
            if (img)
                displayNewFrame(img, false);
            else
                keepSameFrame();
            break;
        default:
            break;
        }
        break;
    default:
        std::cerr << "unknown state, " << evt << std::endl;
        break;
    }
}

void UserInterface::start() {
    if (m_ready == false) {
        std::cerr << __func__ << " : SDL2 not initialized" << std::endl;
        return ;
    }

    SDL_Event e;
    m_deltaWidth = m_math_width / m_width;
    m_deltaHeight = m_math_height / m_height;
    SDL_TimerID timerId = SDL_AddTimer(1000 / NB_FRAMES_PER_SECOND, customEventCb, NULL);

    finiteStateMachine(initialization);
    while (m_continueLoopHook && SDL_WaitEvent(&e))
    {
        switch (e.type) {
            case SDL_KEYDOWN:
                std::cout << "SDL_KEYDOWN: scan code -> " << e.key.keysym.scancode << std::endl;
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        m_continueLoopHook = false;
                        break;
                    case SDL_SCANCODE_SPACE:
                        finiteStateMachine(switchWanted);
                        break;
                    case SDL_SCANCODE_N:
                        finiteStateMachine(nextFrameWanted);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                stop();
                break;
            case SDL_USEREVENT:
                finiteStateMachine(plopEvent);
                break;
            case SDL_WINDOWEVENT:
                switch (e.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        m_width = e.window.data1;
                        m_height = e.window.data2;
                        m_deltaWidth = m_math_width / m_width;
                        m_deltaHeight = m_math_height / m_height;
                        m_surface = SDL_GetWindowSurface(m_win);
                        break;
                    case SDL_WINDOWEVENT_MOVED:
                        std::cout << "window has moved !" << std::endl;
                        break;
                    default:
                        std::cout << "default window event" << std::endl;
                        break;
                }
        }
    }
    SDL_RemoveTimer(timerId);
    m_ready = false;
}

void UserInterface::stop() {
    m_continueLoopHook = false;
}
