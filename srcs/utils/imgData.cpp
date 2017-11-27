
#include <iostream>
#include "imgData.hpp"

using namespace mod1;

ImgData::ImgData() {
}

ImgData::~ImgData() {
}

void ImgData::fillRGBPixel(uint8_t red,
                           uint8_t green,
                           uint8_t blue,
                           int location)
{
    if (location < 0 || location >= SIZE) {
        std::cerr << __func__ << " : Overflow, have " << location << std::endl;
        return ;
    }
    m_map[location].r = red;
    m_map[location].g = green;
    m_map[location].b = blue;
}

void ImgData::cleanImage() {
    bzero(m_map, SIZE * 3);
    m_state = IMG_DATA_CLEAN;
}

void ImgData::cleanImage(uint8_t red,
                         uint8_t green,
                         uint8_t blue)
{
    for (int location = 0; location < SIZE; location++) {
        m_map[location].r = red;
        m_map[location].g = green;
        m_map[location].b = blue;
    }
    m_state = IMG_DATA_CLEAN;
}
