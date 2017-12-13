
#include "renderer.hpp"

using namespace mod1;

Renderer::Renderer()
{
}

Renderer::~Renderer() {}

void Renderer::raytrace(RenderedFrame *img) {


    double prop_x;
    double prop_y;
    prop_x =  grid_width / frame_width;
    prop_y =  grid_height / frame_height;
    for (int y = 0 ; y < FRAME_HEIGHT; y++) {
        for (int x = 0 ; x < FRAME_WIDTH; x++)
        {
            int grid_coord_i = (double)x * prop_x;
            int grid_coord_j = (GRID_HEIGHT - (double)y * prop_y);
            if (GRID[grid_coord_i][grid_coord_j].type == SOLID)
                ((int *)img->m_map)[y * FRAME_WIDTH + x] = 0x00ffffff;
			else if (GRID[grid_coord_i][grid_coord_j].type == FLUID)
                ((int *)img->m_map)[y * FRAME_WIDTH + x] = 0x000000ff;

        }
    }
    prop_x = frame_width / real_width;
    prop_y = frame_height / real_height;

    for (unsigned long int p = 0; p < PARTICLES.size(); p++)
    {
        int x = PARTICLES[p].pos.x * prop_x;
        int y = FRAME_HEIGHT - 1 - PARTICLES[p].pos.y * prop_y;
        int index = y * FRAME_WIDTH + x;
        if (index < 0 || index >= FRAME_SIZE)
            continue ;
        ((int *)img->m_map)[y * FRAME_WIDTH + x] = 0x5ecabb;
    }
 	prop_x =  frame_width / grid_width;
	prop_y =  frame_height / grid_height;
    for (int y = 0 ; y < GRID_HEIGHT; y++) {
        for (int x = 0 ; x < FRAME_WIDTH; x++)
		{
			int img_y = y * prop_y;
			((int *)img->m_map)[img_y * FRAME_WIDTH + x] = 0x00ff0000;
		}
	}
    for (int x = 0 ; x < GRID_WIDTH; x++) {
        for (int y = 0 ; y < FRAME_HEIGHT; y++)
		{
			((int *)img->m_map)[y * FRAME_WIDTH + (int)(x * prop_x)] = 0x00ff0000;
		}
	}
}
