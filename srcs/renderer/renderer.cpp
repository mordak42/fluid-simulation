
#include "renderer.hpp"

using namespace mod1;

Renderer::Renderer(const std::shared_ptr<PhysicItems> &physicItems) :
                                        m_physicItems(physicItems)
{
}

Renderer::~Renderer() {}

void Renderer::raytrace(RenderedFrame *img) {
    int index;

	float frame_width = DEFAULT_RENDERED_FRAME_WIDTH;
	float frame_height = DEFAULT_RENDERED_FRAME_HEIGHT;
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

            index = i * frame_width / MATH_WIDTH + frame_width * j * frame_height / MATH_HEIGHT;
            if (GRID[i][MATH_HEIGHT - 1 - j].type == SOLID) {
                img->m_map[index].r = 0xFF;
                img->m_map[index].g = 0xFF;
                img->m_map[index].b = 0xFF;
            }
        }
    }
/*    for (int p = 0; p < NB_PARTICLES; p++)
    {
        double i = PARTICLES[p].x / DX;
        double j = PARTICLES[p].y / DY;
		index = i * frame_width / MATH_WIDTH + frame_width * (MATH_HEIGHT - j) * frame_height / MATH_HEIGHT;
        img->m_map[index].b = 0xFF;
    }*/
}
