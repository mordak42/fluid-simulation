
#include "displayer.hpp"

using namespace mod1;

Displayer::Displayer() : SdlContext() {
    /* Debug test */
    updateRefCount();
}

Displayer::~Displayer() {
    TTF_CloseFont(m_font);
}

bool Displayer::initFont(const char *pathname, int fontSize) {
    if (m_ready == true) {
        std::cerr << "Displayer overlay already initialized" << std::endl;
        return false;
    }
    if (!TTF_WasInit()) {
        std::cerr << "Cannot initialize Displayer, TTF interface not provided" << std::endl;
        return false;
    }
    m_font = TTF_OpenFont(pathname, fontSize);
    if (m_font == nullptr) {
        std::cerr << "font is null" << std::endl;
        return false;
    }
    m_ready = true;
    return true;
}

bool Displayer::displayMsg(int originWidth, int originHeight, unsigned int color, const char *fmt, ...) {
    if (m_ready == false) {
        std::cerr << "Displayer were never initialized" << std::endl;
        return false;
    }

    va_list argptr;
    va_start(argptr, fmt);
    char str[128];
    vsnprintf(str, 128, fmt, argptr);
    va_end(argptr);

    SDL_Color SDLcolor = {
            (uint8_t)(color >> 24),
            (uint8_t)(color >> 16 & 0xFF),
            (uint8_t)(color >> 8 & 0xFF),
            (uint8_t)(color & 0xFF)};
    SDL_Surface *font_surface = TTF_RenderText_Solid(m_font, str, SDLcolor);
    if (font_surface == NULL)
        return false;
    if (originWidth < 0)
        originWidth = 0;
    if (originHeight < 0)
        originHeight = 0;
    if (originWidth > (m_width - font_surface->w))
        originWidth = m_width - font_surface->w;
    if (originHeight > (m_height - font_surface->h))
        originHeight = m_height - font_surface->h;
    SDL_Rect area = {originWidth, originHeight, font_surface->w, font_surface->h};
    SDL_BlitSurface(font_surface, NULL, m_surface, &area);
    SDL_FreeSurface(font_surface);
    return true;
}
