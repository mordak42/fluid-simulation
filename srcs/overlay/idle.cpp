
#include "idle.hpp"

using namespace mod1;

Idle::Idle(int nbFrames) : SdlContext(), m_nbFrames(nbFrames) {
    /* Debug test */
    updateRefCount();
}

Idle::~Idle() {
    for (int i = 0; i < MAX_IDLE_NUMBER; i++) {
        SDL_FreeSurface(m_font_surface[i]);
    }
    TTF_CloseFont(m_font);
}

int Idle::IdleMeterInit() {
    if (m_ready == true) {
        std::cerr << "Idle overlay already initialized" << std::endl;
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
    for (int i = 0; i < MAX_IDLE_NUMBER; i++) {
        snprintf(nbr, 16, "Idle %.2i%%", i);
        m_font_surface[i] = TTF_RenderText_Solid(m_font, nbr, color);
    }
    m_ready = true;
    return true;
}

void Idle::setIdleStartPoint() {
    if (m_ready == false) {
        std::cerr << "FPS meter were never initialized" << std::endl;
        return;
    }
    using namespace std::chrono;

    m_originTime = high_resolution_clock::now();
}

void Idle::updateIdleField() {
    if (m_ready == false) {
        std::cerr << "FPS meter were never initialized" << std::endl;
        return;
    }
    using namespace std::chrono;

    struct SDL_Rect area = {m_width - m_font_surface[m_savedIdle]->w - PADDING_IDLE_X, PADDING_IDLE_Y, m_font_surface[m_savedIdle]->w, m_font_surface[m_savedIdle]->h};
    SDL_BlitSurface(m_font_surface[m_savedIdle], NULL, m_surface, &area);
}

void Idle::determineIdle() {
    if (m_ready == false) {
        std::cerr << "FPS meter were never initialized" << std::endl;
        return;
    }
    using namespace std::chrono;
    m_count++;
    if (m_count > m_nbFrames / 4) {
        high_resolution_clock::time_point timeNow = high_resolution_clock::now();
        double timeElapsedMs = duration_cast<duration<double>>(timeNow - m_originTime).count() * 1000;
        double ratio = timeElapsedMs / (1000.0 / m_nbFrames);
        m_savedIdle = 100 - (100 * ratio);
        if (m_savedIdle < 0)
            m_savedIdle = 0;
        m_count = 0;
    }
}
