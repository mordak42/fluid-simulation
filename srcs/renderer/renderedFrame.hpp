
#ifndef __RENDERED_FRAME_HPP__
# define __RENDERED_FRAME_HPP__

#include <iostream>

# define FRAME_WIDTH 200
# define FRAME_HEIGHT 200
# define FRAME_SIZE (FRAME_WIDTH * FRAME_HEIGHT)
# define RENDERED_FRAME_BPP 32

namespace mod1
{
class RenderedFrame {
public:
    RenderedFrame();
    ~RenderedFrame();
    RenderedFrame(const RenderedFrame &m) = delete;
    RenderedFrame& operator=(const RenderedFrame &m) = delete;

    void fillRGBPixel(uint8_t red, uint8_t green, uint8_t blue, int location);
    void cleanFrame();
    void cleanFrame(uint8_t red, uint8_t green, uint8_t blue);

    struct t_pix {
        uint8_t a;
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    t_pix m_map[FRAME_SIZE];
};
}

#endif
