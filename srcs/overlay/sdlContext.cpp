
#include "sdlContext.hpp"

using namespace mod1;

SdlContext::SdlContext() {
    init();
}

SdlContext::SdlContext(std::string & windowName) {
    m_windowName = windowName;
    init();
}

SdlContext::SdlContext(int width, int height) {
    m_width = width;
    m_height = height;
    init();
}

SdlContext::SdlContext(int width, int height, std::string & windowName) {
    m_width = width;
    m_height = height;
    m_windowName = windowName;
    init();
}

SdlContext::SdlContext(int width, int height, int posX, int posY, std::string & windowName) {
    m_width = width;
    m_height = height;
    m_posX = posX;
    m_posY = posY;
    m_windowName = windowName;
    init();
}

bool SdlContext::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
        std::cerr << __func__ << " : Cannot initialize SDL" << SDL_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() < 0) {
        std::cerr << __func__ << " : Cannot initialize TTF" << SDL_GetError() << std::endl;
        return false;
    }
    m_win = SDL_CreateWindow(
            m_windowName.c_str(),
            m_posX,
            m_posY,
            m_width,
            m_height,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (m_win == nullptr) {
        std::cerr << __func__ << " : Cannot create window" << std::endl;
        return false;
    }
    return true;
}

SdlContext::~SdlContext() {
    SDL_DestroyWindow(m_win);
    TTF_Quit();
    SDL_Quit();
}

/* Debug test */

void SdlContext::updateRefCount() {
    m_refCount++;
}

int SdlContext::getRefCount() {
    return m_refCount;
}
