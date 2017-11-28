
#ifndef __POOL_HPP__
# define __POOL_HPP__

#include <iostream>
#include <queue>
#include <mutex>

#include "utils/semaphore.hpp"
#include "utils/imgData.hpp"
#include "utils/fifo.hpp"

namespace mod1
{
class Pool {
public:
    Pool(uint32_t nbFrames);
    ~Pool();

    bool init();

    ImgData *popOutdatedFrame(void);
    ImgData *popRenderedFrame(void);
    void pushOutdatedFrame(ImgData *frame);
    void pushRenderedFrame(ImgData *frame);

private:
    std::fifo<ImgData *> m_actives;
    std::fifo<ImgData *> m_inactives;

    std::semaphore m_availabilitySem;
    uint32_t m_nbFrames;
    bool m_ready = false;
};
}
#endif
