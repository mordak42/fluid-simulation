
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
    for (int y = 0 ; y < FRAME_HEIGHT; y++)
        for (int x = 0 ; x < FRAME_WIDTH; x++)
        {
            int grid_coord_i = (double)x * prop_x;
            int grid_coord_j = (GRID_HEIGHT - 1 - (double)y * prop_y);
            if (grid_coord_j < 0)
                grid_coord_j = 0;
            if (GRID[grid_coord_i][grid_coord_j].type == SOLID)
            {
                img->m_map[y * FRAME_WIDTH + x].r = 0xFF;
                img->m_map[y * FRAME_WIDTH + x].g = 0xFF;
                img->m_map[y * FRAME_WIDTH + x].b = 0xFF;
            }
        }
    prop_x = frame_width / real_width;
    prop_y = frame_height / real_height;
    /*
    for (int p = 0; p < NB_PARTICLES; p++)
    {
        double x = PARTICLES[p].x * prop_x;
        double y = FRAME_HEIGHT - PARTICLES[p].y * prop_y;
        img->m_map[(int)(y * FRAME_WIDTH + x)].b = 0xFF;
    }*/
}
