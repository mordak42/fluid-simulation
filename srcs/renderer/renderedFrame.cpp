
#include "renderedFrame.hpp"

#include <string.h>

using namespace mod1;

RenderedFrame::RenderedFrame() {
}

RenderedFrame::~RenderedFrame() {
}

void RenderedFrame::fillRGBPixel(uint8_t red,
                                 uint8_t green,
                                 uint8_t blue,
                                 int location)
{
    if (location < 0 || location >= FRAME_SIZE) {
        std::cerr << __func__ << " : Overflow, have " << location << std::endl;
        return ;
    }
    m_map[location].r = red;
    m_map[location].g = green;
    m_map[location].b = blue;
}

void RenderedFrame::cleanFrame() {
    bzero(m_map, FRAME_SIZE * RENDERED_FRAME_BPP / 8);
}

void RenderedFrame::cleanFrame(uint8_t red,
                               uint8_t green,
                               uint8_t blue)
{
    for (int location = 0; location < FRAME_SIZE; location++) {
        m_map[location].r = red;
        m_map[location].g = green;
        m_map[location].b = blue;
    }
}
