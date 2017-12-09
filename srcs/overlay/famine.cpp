
#include "famine.hpp"

using namespace mod1;

Famine::Famine() : SdlContext() {
    /* Debug test */
    updateRefCount();
}

Famine::~Famine() {
    SDL_FreeSurface(m_font_surface);
    TTF_CloseFont(m_font);
}

bool Famine::initFamine() {
    if (m_ready == true) {
        std::cerr << "Famine overlay already initialized" << std::endl;
        return false;
    }
    if (!TTF_WasInit()) {
        std::cerr << "Cannot initialize Famine, TTF interface not provided" << std::endl;
        return false;
    }

    m_font = TTF_OpenFont("srcs/fonts/Chalkduster.ttf", 25);
    if (m_font == nullptr) {
        std::cerr << "font is null" << std::endl;
        return false;
    }
    SDL_Color color = {255, 255, 255, 0};
    m_font_surface = TTF_RenderText_Solid(m_font, "FAMINE", color);

    if (m_font_surface == NULL)
        return false;
    m_ready = true;
    return true;
}

void Famine::setFamine() {
    if (m_ready == false) {
        std::cerr << "Famine were never initialized" << std::endl;
        return;
    }
    m_onStarvation = true;
    using namespace std::chrono;
    m_originTime = high_resolution_clock::now();
}

void Famine::updateFamineField() {
    if (m_ready == false) {
        std::cerr << "Famine were never initialized" << std::endl;
        return;
    }
    if (m_onStarvation) {
        SDL_Rect area = {PADDING_FAMINE, PADDING_FAMINE, m_font_surface->w, m_font_surface->h};
        SDL_BlitSurface(m_font_surface, NULL, m_surface, &area);

        using namespace std::chrono;
        high_resolution_clock::time_point timeNow = high_resolution_clock::now();
        if (duration_cast<duration<double>>(timeNow - m_originTime).count() > 1)
            m_onStarvation = false;
    }
}
