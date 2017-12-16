
#include "fps.hpp"

using namespace mod1;

Fps::Fps() : SdlContext() {
    /* Debug test */
    updateRefCount();
}

Fps::~Fps() {
    for (int i = 0; i < MAX_FPS_NUMBER; i++) {
        SDL_FreeSurface(m_font_surface[i]);
    }
    TTF_CloseFont(m_font);
}

int Fps::fpsMeterInit() {
    if (m_ready == true) {
        std::cerr << "FPS overlay already initialized" << std::endl;
        return false;
    }
    if (!TTF_WasInit()) {
        std::cerr << "Cannot initialize TTF, TTF interface not provided" << std::endl;
        return false;
    }

    m_font = TTF_OpenFont("srcs/fonts/Chalkduster.ttf", 25);
    if (m_font == nullptr) {
        std::cerr << "font is null" << std::endl;
        return false;
    }
    SDL_Color color = {255, 255, 255, 0};
    char nbr[16 + 1];
    for (int i = 0; i < MAX_FPS_NUMBER; i++) {
        snprintf(nbr, 16, "DPS %.2i", i);
        m_font_surface[i] = TTF_RenderText_Solid(m_font, nbr, color);
    }
    m_ready = true;
    return true;
}

void Fps::setTimeOrigin() {
    if (m_ready == false) {
        std::cerr << "FPS meter were never initialized" << std::endl;
        return;
    }
    using namespace std::chrono;
    m_savedFps = -1;
    m_nbFrames = 0;
    m_originTime = high_resolution_clock::now();
}

void Fps::updateFpsCounter() {
    if (m_ready == false) {
        std::cerr << "FPS meter were never initialized" << std::endl;
        return;
    }
    using namespace std::chrono;

    high_resolution_clock::time_point timeNow = high_resolution_clock::now();
    m_nbFrames++;
    if (duration_cast<duration<double>>(timeNow - m_originTime).count() > 1) {
        m_savedFps = m_nbFrames > 99 ? 99 : m_nbFrames;
        m_nbFrames = 0;
        m_originTime = timeNow;
    }
}

void Fps::updateFpsField() {
    if (m_ready == false) {
        std::cerr << "FPS meter were never initialized" << std::endl;
        return;
    }
    if (m_savedFps < 0)
        return;
    struct SDL_Rect area = {m_width - m_font_surface[m_savedFps]->w - PADDING_FPS_W, PADDING_FPS_H, m_font_surface[m_savedFps]->w, m_font_surface[m_savedFps]->h};
    SDL_BlitSurface(m_font_surface[m_savedFps], NULL, m_surface, &area);
}
