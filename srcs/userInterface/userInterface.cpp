
#include "userInterface.hpp"

using namespace mod1;

UserInterface::UserInterface(const std::shared_ptr<mod1::Pool> &pool,
                             int width,
                             int height) :
                                m_pool(pool),
                                m_width(width),
                                m_height(height)
{
}

UserInterface::~UserInterface() {}

bool UserInterface::init() {
    if (m_ready == true) {
        std::cerr << __func__ << " : SDL2 already initialized" << std::endl;
        return false;
    }
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
        std::cerr << __func__ << " : Cannot init SDL" << SDL_GetError() << std::endl;
        return false;
    }

    m_win = SDL_CreateWindow("MOD 1",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_width,
            m_height,
            SDL_WINDOW_SHOWN);
    if (m_win == nullptr) {
        std::cerr << __func__ << " : Cannot create window" << std::endl;
        return false;
    }
    //m_surface = SDL_GetWindowSurface(m_win);
    m_renderer = SDL_CreateRenderer(m_win, -1, SDL_RENDERER_ACCELERATED);
    m_ready = true;
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

void UserInterface::start() {
    if (m_ready == false) {
        std::cerr << __func__ << " : SDL2 not initialized" << std::endl;
        return ;
    }

    bool continueLoopHook = true;
    SDL_Event e;
    ImgData *img = nullptr;
    Uint32 delay = 1000 / 50;
    SDL_TimerID timerId = 0;

    while (continueLoopHook && SDL_WaitEvent(&e))
    {
        switch (e.type) {
            case SDL_KEYDOWN:
                std::cout << "SDL_KEYDOWN: scancode -> " << e.key.keysym.scancode << std::endl;
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        continueLoopHook = false;
                        break;
                    case SDL_SCANCODE_S:
                        std::cout << "touch start" << std::endl;
                        if (timerId == 0)
                            timerId = SDL_AddTimer(delay, customEventCb, NULL);
                        break;
                    case SDL_SCANCODE_H:
                        std::cout << "touch halt" << std::endl;
                        if (timerId) {
                            SDL_RemoveTimer(timerId);
                            timerId = 0;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                continueLoopHook = false;
                break;
            case SDL_USEREVENT:
                std::cout << "tick at " << SDL_GetTicks() << std::endl;
                img = m_pool->popRenderedFrame();
                if (img == nullptr)
                    break;
                //SDL_UpdateWindowSurface(m_win);
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
                SDL_RenderClear(m_renderer);
                SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
                for (int i = 0; i < SIZE; i++) {
                    if (img->m_map[i].r != 0) {
                        int x = i % 1920;
                        int y = i / 1920;
                        std::cout << "founded at ! " << i << " x=" << x << " y=" << y << std::endl;
                        SDL_RenderDrawPoint(m_renderer, x, y); //Renders on middle of screen.
                        SDL_RenderDrawPoint(m_renderer, x + 1, y);
                        SDL_RenderDrawPoint(m_renderer, x, y + 1);
                        SDL_RenderDrawPoint(m_renderer, x + 1, y + 1);
                    }
                }
                m_pool->pushOutdatedFrame(img);
                SDL_RenderPresent(m_renderer);
                break;
            default:
                break;
        }
    }
    SDL_DestroyWindow(m_win);
    SDL_RemoveTimer(timerId);
    SDL_Quit();
}
