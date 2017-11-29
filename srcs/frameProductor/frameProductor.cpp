#include "frameProductor.hpp"
#include <unistd.h>

using namespace mod1;

FrameProductor::FrameProductor(const std::shared_ptr<mod1::Pool> &pool) : m_pool(pool) {
}

FrameProductor::~FrameProductor() {}

void FrameProductor::start() {
     m_keepGoing = true;
     std::thread instance(&FrameProductor::threadHandler, this);
     instance.detach();
}

void FrameProductor::stop() {
    m_keepGoing = false;
}

void FrameProductor::threadHandler() {
    const int ox = MATH_WIDTH / 2;
    const int oy = MATH_HEIGHT / 2;
    const int radius = MATH_HEIGHT / 4;
    int x = -radius / 2;
    int y;
    int direction;

    while (m_keepGoing) {
        usleep(1000000 / 20);
        ImgData *img = m_pool->popOutdatedFrame();
        if (img == NULL)
            continue;
        img->cleanImage();

        if (x == -(radius / 2))
            direction = 1;
        if (x == (radius / 2))
            direction = -1;
        y = sqrt((radius * radius) - (x * x));
        if (direction > 0) {
            img->fillRGBPixel(255, 255, 255, ((oy + y) * MATH_WIDTH) + (ox + x));
            x += 2;
        }
        else {
            img->fillRGBPixel(255, 255, 255, ((oy - y) * MATH_WIDTH) + (ox + x));
            x -= 2;
        }

        (void)ox;
        (void)oy;
        (void)radius;
        (void)x;
        (void)y;
        (void)direction;
        m_pool->pushRenderedFrame(img);
    }
//    std::terminate();
}
