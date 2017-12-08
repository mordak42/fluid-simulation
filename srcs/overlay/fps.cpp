
#include "fps.hpp"

using namespace mod1;

Fps::Fps() {
}

Fps::~Fps() {
//    if (m_ready)
//        TTF_CloseFont(m_font);
}

int Fps::init() {
    if (m_ready == true) {
        std::cerr << "FPS overlay already initialized" << std::endl;
        return false;
    }
    if (!TTF_WasInit() && TTF_Init() < 0) {
        std::cerr << "Cannot initialize TTF" << std::endl;
        return false;
    }

    m_font = TTF_OpenFont("srcs/fonts/Chalkduster.ttf", 25);
    if (m_font == nullptr) {
        std::cerr << "font is null" << std::endl;
        return false;
    }
    m_ready = true;
    return true;
}

void Fps::setTimeOrigin() {
    using namespace std::chrono;

    m_originTime = high_resolution_clock::now();
}

void Fps::updateFpsCounter() {
    using namespace std::chrono;

    high_resolution_clock::time_point timeNow = high_resolution_clock::now();
    m_nbFrames++;
    if (duration_cast<duration<double>>(timeNow - m_originTime).count() > 1) {
        std::cout << "FPS = " << m_nbFrames << std::endl;
        m_nbFrames = 0;
        m_originTime = timeNow;
    }
}

void Fps::updateIddleField() {
}

void Fps::fillInformations(SDL_Surface *screen, bool enableDisplaying) {
    (void)screen;
    (void)enableDisplaying;
}
