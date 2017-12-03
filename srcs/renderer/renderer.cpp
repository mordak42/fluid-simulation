
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
            double ratio_x = (double)x / frame_width;
            double ratio_y = (double)y / frame_height;
            
            double grid_x = grid_width * ratio_x;
            double grid_y = grid_height - 1 - (grid_height - 1) * ratio_y;
            if (GRID[(int)grid_x][(int)grid_y].type == SOLID) {
                img->m_map[y * (int)frame_width + x].r = 0xFF;
                img->m_map[y * (int)frame_width + x].g = 0xFF;
                img->m_map[y * (int)frame_width + x].b = 0xFF;
            }
            /*if ((int)grid_x == 199 && (int)grid_y == 199)
            {
            std::cout << "grid_x " << grid_x << std::endl;
            std::cout << "grid_y " <<  grid_y << std::endl;
            }*/
/*            (void)m_physicItems;
            int grid_coord_i = (double)x / frame_width * grid_width;
            int grid_coord_j = (GRID_HEIGHT - 1 - (double)x / frame_height * grid_height);
            if (GRID[grid_coord_i][grid_coord_j].type == SOLID)
            {
                img->m_map[y * FRAME_WIDTH + x].r = 0xFF;
                img->m_map[y * FRAME_WIDTH + x].g = 0xFF;
                img->m_map[y * FRAME_WIDTH + x].b = 0xFF;
            }
            */
        }
        for (int p = 0; p < NB_PARTICLES; p++)
          {
          double i = PARTICLES[p].x / DX;
          double j = PARTICLES[p].y / DY;
          index = i * frame_width / GRID_WIDTH + frame_width * (GRID_HEIGHT - j) * frame_height / GRID_HEIGHT;
          img->m_map[index].b = 0xFF;
          }
}
