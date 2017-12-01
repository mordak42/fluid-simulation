#include "pressurer.hpp"

namespace mod1
{

Pressurer::Pressurer(struct velocity_field **grid_u,
                     struct velocity_field **grid_v,
                     struct cell **grid)
                     : m_grid_u(grid_u),
                       m_grid_v(grid_v),
					   m_grid(grid) {}

Pressurer::~Pressurer() {
}

void Pressurer::update_velocity(void) {
    double scale = 1;

    for (int i = 0 ; i < MATH_WIDTH; i++) {
        for (int j = 0 ; j < MATH_HEIGHT; j++) {
            if (i > 0 && (m_grid[i][j].type == FLUID || m_grid[i - 1][j].type == FLUID))
            {
                if (m_grid[i][j].type == SOLID || m_grid[i - 1][j].type == SOLID)
                    m_grid_u[i][j].val = 0;
                else
                    m_grid_u[i][j].val -= scale * (m_grid[i][j].pressure - m_grid[i - 1][j].pressure);
            }
            if (j > 0 && (m_grid[i][j].type == FLUID || m_grid[i][j - 1].type == FLUID))
            {
                if (m_grid[i][j].type == SOLID || m_grid[i][j - 1].type == SOLID)
                    m_grid_v[i][j].val = 0;
                else
                    m_grid_v[i][j].val -= scale * (m_grid[i][j].pressure - m_grid[i][j - 1].pressure);
            }
        }
    }
}

void Pressurer::solve_pressure(void) {
    (void)m_grid_u;
    (void)m_grid_v;
}
}
