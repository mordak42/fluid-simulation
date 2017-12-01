
#ifndef __RENDERED_FRAME_HPP__
# define __RENDERED_FRAME_HPP__

# define DEFAULT_RENDERED_FRAME_WIDTH 2000
# define DEFAULT_RENDERED_FRAME_HEIGHT 1000
# define DEFAULT_RENDERED_FRAME_SIZE \
        (DEFAULT_RENDERED_FRAME_WIDTH * DEFAULT_RENDERED_FRAME_HEIGHT)
# define RENDERED_FRAME_BPP 24

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
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    t_pix m_map[DEFAULT_RENDERED_FRAME_SIZE];
};
}

#endif
