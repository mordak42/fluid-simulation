
#ifndef __POOL_HPP__
# define __POOL_HPP__

#include <iostream>
#include <queue>
#include <mutex>

#include "utils/semaphore.hpp"
#include "utils/imgData.hpp"

namespace mod1
{
class Pool {
public:
    Pool(unsigned long);
    ~Pool();

    bool init();

    ImgData *popOutdatedFrame(void);
    ImgData *popRenderedFrame(void);
    void pushOutdatedFrame(ImgData &frame);
    void pushRenderedFrame(ImgData &frame);

private:
    std::queue<ImgData> m_actives;
    std::queue<ImgData> m_inactives;
    std::semaphore m_availabilitySem;
    unsigned long m_nbFrames;
    bool m_ready = false;
};
}

#endif
