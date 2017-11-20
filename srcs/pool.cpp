
#include "pool.hpp"

using namespace mod1;

Pool::Pool() {
    std::cout << "Pool initialisation" << std::endl;
}

Pool::~Pool() {
    m_ready = false;

    size_t tmp;

    tmp = m_actives.size();
    std::cout << tmp << std::endl;
    for (size_t i = 0; i < tmp; i++)
        m_actives.pop();

    tmp = m_inactives.size();
    std::cout << tmp << std::endl;
    for (size_t i = 0; i < tmp; i++)
        m_inactives.pop();

    std::cout << "Pool terminated" << std::endl;
}

bool Pool::init(int size) {
    for (int i = 0; i < size; i++)
        m_inactives.emplace();                                                    // TODO FAIL ALLOC
    m_ready = true;
    return true;
}

bool Pool::drawOnRawImage(ImgData **output) {
    if (m_ready == false)
        return false;

    if (m_inactives.size() > 0) {
        ImgData &frame = m_inactives.front();
        frame.isReady = false;
        m_actives.push(frame);
        *output = &frame;
        return true;
    }
    return false;
}

bool Pool::getRenderedImage(ImgData **output) {
    if (m_ready == false)
        return false;

    if (m_actives.size() > 0 && m_actives.front().isReady == true) {
        ImgData &frame = m_actives.front();
        frame.isReady = false;
        m_inactives.push(frame);
        *output = &frame;
        return true;
    }
    return false;
}
