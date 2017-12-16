
#ifndef __BMP_HPP__
# define __BMP_HPP__

#include "overlay/sdlContext.hpp"

#include <stdint.h>

namespace mod1
{
class Bmp : public virtual SdlContext
{

#define PATH "screenshoots/"

#define BPP 24
#define PLANES 1
#define COMPRESSION 0
#define XPIXELPERMETER 0x130B
#define YPIXELPERMETER 0x130B

#pragma pack(push, 1)
struct fileHeader {
    uint8_t signature[2];
    uint32_t filesize;
    uint32_t	 reserved;
    uint32_t	 fileoffset_to_pixelarray;
};

struct bitmapInfoHeader {
    uint32_t dibheadersize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t	 bitsperpixel;
    uint32_t	 compression;
    uint32_t	 imagesize;
    uint32_t ypixelpermeter;
    uint32_t	 xpixelpermeter;
    uint32_t	 numcolorspallette;
    uint32_t mostimpcolor;
};

struct globalHeader
{
    struct fileHeader header;
    struct bitmapInfoHeader bitmapHeader;
};
#pragma pack(pop)

public:
    Bmp();
    ~Bmp();

protected:
    bool saveImage(std::string basename);

private:
    void fillPixelBuffer(uint8_t *output, uint8_t *input);
};
}
#endif
