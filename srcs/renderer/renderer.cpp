
#include "renderer.hpp"

using namespace mod1;

Renderer::Renderer(const std::shared_ptr<PhysicItems> &physicItems) :
                                        m_physicItems(physicItems)
{
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
            if (GRID[i][MATH_HEIGHT - 1 - j].type == SOLID) {
                img->m_map[index].r = 0xFF;
                img->m_map[index].g = 0xFF;
                img->m_map[index].b = 0xFF;
            }
        }
    }
    for (int p = 0; p < NB_PARTICLES; p++)
    {
        double i = PARTICLES[p].x / DX;
        double j = PARTICLES[p].y / DY;
        index = i + MATH_WIDTH * (MATH_HEIGHT - j);
        img->m_map[index].b = 0xFF;
    }
}
