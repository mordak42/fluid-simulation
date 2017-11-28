#ifndef __FRAME_PRODUCTOR_HPP__
# define __FRAME_PRODUCTOR_HPP__

#include <iostream>
#include <thread>
#include "pool.hpp"
#include "renderer/renderer.hpp"
#include "physician/physician.hpp"

namespace mod1
{
class FrameProductor
{
public:
    FrameProductor(const std::shared_ptr<mod1::Pool> &pool);
    ~FrameProductor();
    void start();
    void stop();

private:
    void threadHandler();

    const std::shared_ptr<Pool> m_pool;
    std::unique_ptr<Renderer> m_renderer = nullptr;
    std::unique_ptr<Physician> m_physician = nullptr;
    bool m_keepGoing = false;
};
}

#endif
