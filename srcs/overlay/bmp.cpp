
#include "bmp.hpp"

using namespace mod1;

Bmp::Bmp() : SdlContext() {
    /* Debug test */
    updateRefCount();
}

Bmp::~Bmp() {};

bool Bmp::saveImage(std::string basename) {
    globalHeader header;
    FILE *file;
    uint8_t *pixelbuffer;

    std::string filename = PATH + basename + ".bmp";
    std::cout << "Creating file " << filename.c_str() << std::endl;

    if (!(file = fopen(filename.c_str(), "wb+"))) {
        std::cerr << "Cannot create file " << filename << std::endl;
        return false;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(m_win);
    if (surface == NULL) {
        std::cerr << "Cannot allocate memory" << std::endl;
        return false;
    }

    if (!(pixelbuffer = (uint8_t *)malloc(m_height * m_width * BPP / 8))) {
        std::cerr << "Cannot allocate memory" << std::endl;
        return false;
    }

    memcpy((char *)header.header.signature, "BM", 2);
    header.header.filesize = (m_width * m_height) + sizeof(globalHeader);
    header.header.fileoffset_to_pixelarray = sizeof(globalHeader);
    header.bitmapHeader.dibheadersize = sizeof(struct bitmapInfoHeader);
    header.bitmapHeader.width = m_width;
    header.bitmapHeader.height = m_height;
    header.bitmapHeader.planes = PLANES;
    header.bitmapHeader.bitsperpixel = BPP;
    header.bitmapHeader.compression = COMPRESSION;
    header.bitmapHeader.imagesize = (m_width * m_height * BPP / 8);
    header.bitmapHeader.ypixelpermeter = YPIXELPERMETER;
    header.bitmapHeader.xpixelpermeter = XPIXELPERMETER;
    header.bitmapHeader.numcolorspallette = 0;

    fillPixelBuffer(pixelbuffer, (uint8_t *)surface->pixels);

    fwrite(&header, 1, sizeof(header), file);
    fwrite(pixelbuffer, 1, header.bitmapHeader.imagesize, file);

    free(pixelbuffer);
    fclose(file);
    return true;
}

void Bmp::fillPixelBuffer(uint8_t *output, uint8_t *input)
{
    size_t i;
    uint8_t *ptr;
    int c;
    int p;

    p = m_height - 1;
    ptr = output + (p * m_width * 3);
    c = 0;
    i = 0;
    while (p >= 0) {
        if ((i % 4) == 3)
            i++;
        ptr[c++] = input[i];
        if (c == (m_width * 3)) {
            p--;
            ptr = output + (p * m_width * 3);
            c = 0;
        }
        i++;
    }
}
