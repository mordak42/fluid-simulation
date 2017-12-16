
#include "renderer.hpp"

using namespace mod1;

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::raytrace(RenderedFrame *img) {
    double prop_x;
    double prop_y;

 /* TODO Border equation need to be verified */
#ifndef BORDER
    prop_x =  grid_width / frame_width;
#else
    prop_x =  (grid_width - BORDER_LENGTH) / frame_width;
#endif
    prop_y =  grid_height / frame_height;

    /* Draw grid nature */
    for (int y = 0 ; y < FRAME_HEIGHT; y++) {
        for (int x = 0 ; x < FRAME_WIDTH; x++)
        {
#ifndef BORDER
            int grid_coord_i = (double)x * prop_x;
#else
            int grid_coord_i = (BORDER_LENGTH / 2) + (double)x * prop_x;
#endif
            int grid_coord_j = (GRID_HEIGHT - (double)y * prop_y);

            if (GRID[grid_coord_i][grid_coord_j].type == SOLID)
                ((int *)img->m_map)[y * FRAME_WIDTH + x] = 0x00ffffff;
#ifdef GRID_DEBUG
			else if (GRID[grid_coord_i][grid_coord_j].type == FLUID)
                ((int *)img->m_map)[y * FRAME_WIDTH + x] = 0x000000ff;
			else if (GRID[grid_coord_i][grid_coord_j].type == SURROUND)
                ((int *)img->m_map)[y * FRAME_WIDTH + x] = 0x0000ffff;
#endif
        }
    }
#ifndef BORDER
    prop_x = frame_width / real_width;
#else
    prop_x = frame_width / (real_width * (double)(1. - (BORDER_LENGTH / GRID_WIDTH)));
#endif
    prop_y = frame_height / real_height;

    /* Draw particles */
    for (unsigned long int p = 0; p < PARTICLES.size(); p++)
    {
#ifndef BORDER
        int x = PARTICLES[p].pos.x * prop_x;
#else
        int x = PARTICLES[p].pos.x * prop_x - ((BORDER_LENGTH / GRID_WIDTH / 2) * frame_width);
#endif
        int y = FRAME_HEIGHT - 1 - PARTICLES[p].pos.y * prop_y;

        int index = y * FRAME_WIDTH + x;
        if (index < 0 || index >= FRAME_SIZE)
            continue ;
        ((int *)img->m_map)[y * FRAME_WIDTH + x] = 0x5ecabb;
    }
}
