
#include "renderer.hpp"

using namespace mod1;

Renderer::Renderer(const std::shared_ptr<PhysicItems> &physicItems) :
                                        m_physicItems(physicItems)
{
}

Renderer::~Renderer() {}

void Renderer::raytrace(RenderedFrame *img) {


    double prop_x =  grid_width / frame_width;
    double prop_y =  grid_height / frame_height;
    for (int y = 0 ; y < FRAME_HEIGHT; y++) {
        for (int x = 0 ; x < FRAME_WIDTH; x++)
        {
            int grid_coord_i = (double)x * prop_x;
            int grid_coord_j = (GRID_HEIGHT - 1 - (double)y * prop_y);
            if (GRID[grid_coord_i][grid_coord_j].type == SOLID)
                ((int *)img->m_map)[y * FRAME_WIDTH + x] = 0x00ffffff;
        }
    }
    prop_x = frame_width / real_width;
    prop_y = frame_height / real_height;

    for (unsigned long int p = 0; p < PARTICLES.size(); p++)
    {
        int x = PARTICLES[p].x * prop_x;
        int y = FRAME_HEIGHT - 1 - PARTICLES[p].y * prop_y;
        int index = y * FRAME_WIDTH + x;
        if (index < 0 || index >= FRAME_SIZE)
            continue ;
        ((int *)img->m_map)[y * FRAME_WIDTH + x] = 0x5ecabb;
    }
}
