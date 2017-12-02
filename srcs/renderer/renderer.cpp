
#include "renderer.hpp"

using namespace mod1;

Renderer::Renderer(struct particle *particles, struct cell **grid) :
                                                        m_particles(particles),
                                                        m_grid(grid)

{
    int index;
    for (int i = 0 ; i < MATH_WIDTH; i++)
    {
        for (int j = 0 ; j < MATH_HEIGHT; j++)
        {
            /*
             *  ---------
             *  |
             *  |
             *  |
             *  |--------
             */

            index = i + MATH_WIDTH * j;
            if (grid[0][0].type == SOLID) {
    //            img->m_map[index].r = 0xFF;
//                img->m_map[index].g = 0xFF;
//                img->m_map[index].b = 0xFF;
            }
            particles[0].v = 24;
        }
    }
}

Renderer::~Renderer() {}

void Renderer::raytrace(RenderedFrame *img) {
    int index;

    for (int i = 0 ; i < MATH_WIDTH; i++)
    {
        for (int j = 0 ; j < MATH_HEIGHT; j++)
        {
            /*
             *  ---------
             *  |
             *  |
             *  |
             *  |--------
             */

            index = i + MATH_WIDTH * j;
            if (m_grid[i][MATH_HEIGHT - 1 - j].type == SOLID) {
                img->m_map[index].r = 0xFF;
                img->m_map[index].g = 0xFF;
                img->m_map[index].b = 0xFF;
            }
        }
    }
    for (int p = 0; p < NB_PARTICLES; p++)
    {
        std::cout << "DX" << DX << std::endl;
        std::cout << "DY" << DY << std::endl;
        double i = m_particles[p].x / DX;
        double j = m_particles[p].y / DY;
        std::cout << "m_particles x " << m_particles[p].x << std::endl;
        std::cout << "m_particles y " << m_particles[p].y << std::endl;
        std::cout << "i " << i << std::endl;
        std::cout << "j " << j << std::endl;
        index = i + MATH_WIDTH * (MATH_HEIGHT - j);
        img->m_map[index].b = 0xFF;
    }
}
