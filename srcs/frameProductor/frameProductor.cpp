#include "frameProductor.hpp"
#include <unistd.h>
#include <thread>

using namespace mod1;

FrameProductor::FrameProductor(const std::shared_ptr<mod1::Pool> &pool) : m_pool(pool) {
}

FrameProductor::~FrameProductor() {}

void FrameProductor::start() {
     std::thread instance(&FrameProductor::threadHandler, this);
     instance.detach();
}

#define OX 960;
#define OY 540;
#define RADIUS 200;


void FrameProductor::threadHandler() {
    const int ox = 960;
    const int oy = 540;
    const int radius = 200;
    int x = -100;
    int y;
    int direction;

    while (true) {
        usleep(1000000 / 100);
        ImgData *img = m_pool->popOutdatedFrame();
        if (img == NULL)
            continue;
        img->cleanImage();

        if (x == -(radius / 2))
            direction = 1;
        if (x == (radius / 2))
            direction = -1;
        y = sqrt((radius * radius) - (x * x));
        std::cout << x << " : " << y << std::endl;
        if (direction > 0) {
            img->fillRGBPixel(255, 255, 255, ((oy + y) * 1920) + (ox + x));
            x += 2;
        }
        else {
            img->fillRGBPixel(255, 255, 255, ((oy - y) * 1920) + (ox + x));
            x -= 2;
        }

        m_pool->pushRenderedFrame(img);
    }
}
