
#ifndef __IMG_DATA_HPP__
# define __IMG_DATA_HPP__

#include "common.hpp"

#ifdef __cplusplus
extern "C" {
#endif
#include "SDL2/SDL.h"
#ifdef __cplusplus
}
#endif

namespace mod1
{
class ImgData {
public:
    ImgData();
    ~ImgData();
    ImgData(const ImgData &m) = delete;
    ImgData& operator=(const ImgData &m) = delete;

    void fillRGBPixel(uint8_t red, uint8_t green, uint8_t blue, int location);
    void cleanImage();
    void cleanImage(uint8_t red, uint8_t green, uint8_t blue);

    enum e_ImgData_state {
        IMG_DATA_CLEAN,
        IMG_DATA_CLEANNING,
        IMG_DATA_DIRTY
    };
    e_ImgData_state m_state = IMG_DATA_DIRTY;

    struct t_pix {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    t_pix m_map[MATH_SIZE];
};
}

#endif
