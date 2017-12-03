
#include "renderer.hpp"

using namespace mod1;

Renderer::Renderer(const std::shared_ptr<PhysicItems> &physicItems) :
                                        m_physicItems(physicItems)
{
}

Renderer::~Renderer() {}

void Renderer::raytrace(RenderedFrame *img) {
    int index;
    for (int y = 0 ; y < FRAME_HEIGHT; y++)
        for (int x = 0 ; x < FRAME_WIDTH; x++)
        {
            (void)m_physicItems;
            int grid_coord_i = FRAME_TO_GRID_WIDTH(x);
            int grid_coord_j = FRAME_TO_GRID_HEIGHT(y);
            if (GRID[grid_coord_i][grid_coord_j].type == SOLID)
            {
                img->m_map[y * FRAME_WIDTH + x].r = 0xFF;
                img->m_map[y * FRAME_WIDTH + x].g = 0xFF;
                img->m_map[y * FRAME_WIDTH + x].b = 0xFF;
            }
        }
        for (int p = 0; p < NB_PARTICLES; p++)
          {
          double i = PARTICLES[p].x / DX;
          double j = PARTICLES[p].y / DY;
          index = i * frame_width / GRID_WIDTH + frame_width * (GRID_HEIGHT - j) * frame_height / GRID_HEIGHT;
          img->m_map[index].b = 0xFF;
          }
}
