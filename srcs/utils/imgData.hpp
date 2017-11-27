
#ifndef __IMG_DATA_HPP__
# define __IMG_DATA_HPP__

# define SIZE 1920 * 1080
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
    t_pix m_map[SIZE];
};
}

#endif
