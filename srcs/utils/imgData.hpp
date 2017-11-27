
#ifndef __IMG_DATA_HPP__
# define __IMG_DATA_HPP__

# define SIZE 1920 * 1080 * 3
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
	enum t_ImgData_state {
		IMG_DATA_CLEAN,
		IMG_DATA_CLEANNING,
		IMG_DATA_DIRTY
	};

    SDL_Surface		*surface;
    bool			isReady = IMG_DATA_DIRTY;
};
}

#endif
