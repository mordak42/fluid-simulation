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
    int i = 0;
	while (true) {
		usleep(1000000 / 30);
		std::cout << "productor try to make new frame" << std::endl;
		ImgData *img = m_pool->popOutdatedFrame();
		if (img == NULL) {
            std::cout << "productor cannot" << std::endl;
			continue;
        }
        img->img[10] = i++;
        std::cout << "making frame " << (i - 1) << std::endl;
		m_pool->pushRenderedFrame(img);
		(void)img;
	}
}
