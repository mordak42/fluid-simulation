#include "frameProductor.hpp"
#include <unistd.h>

/*          
 *      the MAC grid
 *
 *          j, v
 *          |
 *          |
 *          |
 *          |
 *          |---------------- i, u
 *          /
 *         /
 *        /
 *       /
 *      k, w
 *
 *      p(i,j,k) = pi,j,k, 
 *      u(i,j,k) = ui−1/2,j,k 
 *      v(i,j,k) = vi,j−1/2,k
 *      w(i,j,k) = wi,j,k−1/2
 *
 * in 2 dimensions:
 *                                
 *                         v(i, j + 1/2) <=> v(i, j + 1)
 *                           ^
 *                    _______|_______
 *                    |             |
 *                    |             |
 *  u(i - 1/2, j)   <-|  p(i,j)     |-> u(i + 1/2, j) <=> v(i + 1, j)
 *  <=> u(i - 1/2, j) |             |
 *                    |             |
 *                    ---------------
 *                           |
 *                         v(i, j - 1/2) <=> v(i, j)
 *              
 */

using namespace mod1;

FrameProductor::FrameProductor(const std::shared_ptr<mod1::Pool> &pool) : m_pool(pool)
{
    m_physician.reset(new Physician(m_particles));
}

FrameProductor::~FrameProductor() {}

void FrameProductor::start() {
     m_keepGoing = true;
     std::thread instance(&FrameProductor::threadHandler, this);
     instance.detach();
}

void FrameProductor::stop() {
    m_keepGoing = false;
}

#define SIZE_EXEMPLE 5

static void    debug_poly(Polynom poly)
{
    for (int i = poly.m_nb_coefs - 1; i >= 0; i--) {
        std::cout << ' ' << poly.m_coefs[i];
        std::cout << "*x^" << i << " + ";
    }
    std::cout << '\n';
}

/*
 * google exemple:
 * 3.77604e-08*x^4 +  -6.61458e-05*x^3 +  0.0316146*x^2 +  -3.22917*x^1 +  0
*/

//bool FrameProductor::parseFile(const char &buff) {
bool FrameProductor::parseFile() {
    struct point p[SIZE_EXEMPLE];
    p[0].x = 0;
    p[0].y = 0;
    p[1].x = 200;
    p[1].y = 150;
    p[2].x = 400;
    p[2].y = 500;
    p[3].x = 600;
    p[3].y = 50;
    p[4].x = 1000;
    p[4].y = 0;
    m_groundLevel = lagrange(p, SIZE_EXEMPLE);
    debug_poly(m_groundLevel);
    for (int y = -1000 ; y < 1000; y++)
        for (int x = 0 ; x < 1000; x++) {
            m_grid[y + 1000][x] = ((m_groundLevel.eval((double)x) - y)) > 0 ? 1 : 0;
        }
    return true;
}

void FrameProductor::raytrace(ImgData *img) {
    int index;

    for (int y = 0; y < 2000; y++) {
        for (int x = 0 ; x < 1000; x++) {
            index = y * 1000 + x;
            if (m_grid[1999 - y][x] == 1) {
                img->m_map[index].r = 0xFF;
                img->m_map[index].g = 0xFF;
                img->m_map[index].b = 0xFF;
            }
        }
    }
}

void FrameProductor::threadHandler() {
    while (m_keepGoing) {
        ImgData *img = m_pool->popOutdatedFrame();
        if (img == NULL)
            continue;
        img->cleanImage();
        raytrace(img);
        m_pool->pushRenderedFrame(img);
    }
}
