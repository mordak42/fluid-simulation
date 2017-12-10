
#include "userInterface.hpp"

using namespace mod1;

UserInterface::UserInterface(const std::shared_ptr<lib::Pool<RenderedFrame>> &pool,
                             int width,
                             int height) :
                                SdlContext(width, height),
                                Fps(),
                                Idle(NB_FRAMES_PER_SECOND),
                                Famine(),
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

    /* Debug test */
    std::cout << "Actual parent refCount is " << getRefCount() << "/4" << std::endl;
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

inline int UserInterface::Rgb_to_int(int r, int g, int b) {
    return (r << 16 | g << 8 | b);
}

#include <unistd.h>

void UserInterface::start() {
    if (m_ready == false) {
        std::cerr << __func__ << " : SDL2 not initialized" << std::endl;
        return ;
    }

    SDL_Event e;
    RenderedFrame *img;
    Uint32 delay = 1000 / NB_FRAMES_PER_SECOND;
   // SDL_TimerID timerId = 0;

    float math_width = FRAME_WIDTH;
    float math_height = FRAME_HEIGHT;
    float deltaWidth = math_width / m_width;
    float deltaHeight = math_height / m_height;

    setTimeOrigin();
    SDL_TimerID timerId = SDL_AddTimer(delay, customEventCb, NULL);
    bool displayWanted = false;
    bool oneTimeDisplay = true;
    while (m_continueLoopHook && SDL_WaitEvent(&e))
    {
        switch (e.type) {
            case SDL_KEYDOWN:
                std::cout << "SDL_KEYDOWN: scan code -> " << e.key.keysym.scancode << std::endl;
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        m_continueLoopHook = false;
                        break;
                    case SDL_SCANCODE_S:
                        std::cout << "touch start" << std::endl;
                        displayWanted = true;
                        break;
                    case SDL_SCANCODE_H:
                        std::cout << "touch halt" << std::endl;
                        displayWanted = false;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                stop();
                break;
            case SDL_USEREVENT:
                if (!displayWanted && !oneTimeDisplay)
                    break;
                img = m_pool->popRenderedItem();
                if (img) {
                    oneTimeDisplay = false;
                    setIdleStartPoint();
                    updateFpsCounter();
                    int h = m_width;
                    for (int y = 0; y < m_height; y++) {
                        double j = (int)(deltaHeight * y) * math_width;
                        for (int i = h - m_width; i < h; i++) {
                            ((int *)m_surface->pixels)[i] = ((int *)img->m_map)[(int)(j)];
                            j += deltaWidth;
                        }
                        h += m_width;
                    }
                    m_pool->pushOutdatedItem(img);
                    updateFamineField();
                    updateFpsField();
                    updateIdleField();
                    SDL_UpdateWindowSurface(m_win);
                    determineIdle();
                }
                else {
                    setFamine();                    //  TODO SDL_UpdateWindowSurfaceRects
                    updateFamineField();
                    updateFpsField();
                    updateIdleField();
                    SDL_UpdateWindowSurface(m_win);
                }
                break;
            case SDL_WINDOWEVENT:
                switch (e.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        m_width = e.window.data1;
                        m_height = e.window.data2;
                        m_surface = SDL_GetWindowSurface(m_win);
                        std::cout << "new size = " << m_width << " - " << m_height << std::endl;
                        deltaWidth = math_width / m_width;
                        deltaHeight = math_height / m_height;
                        if (displayWanted == false) {
#ifdef __APPLE__
                            // Work-Around on OSX, when switch to fullScreen mode, resize event come sometimes too soon.
                            usleep(250000);
#endif
                            oneTimeDisplay = true;
                        }
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
