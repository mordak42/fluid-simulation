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

void FrameProductor::threadHandler() {
    while (true) {
        usleep(1000000 / 30);
        ImgData *img = m_pool->popOutdatedFrame();
        if (img == NULL)
            continue;
        m_pool->pushRenderedFrame(img);
        (void)img;
    }
}
