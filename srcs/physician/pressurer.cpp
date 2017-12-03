
#include "pressurer.hpp"

using namespace mod1;

Pressurer::Pressurer(const std::shared_ptr<PhysicItems> &physicItems) :
                                    PhysicLaw(),
                                    m_physicItems(physicItems)
{}

Pressurer::~Pressurer() {}

void Pressurer::update_velocity(void) {
    double scale = 1;

    for (int i = 0 ; i < GRID_WIDTH; i++)
    for (int j = 0 ; j < GRID_HEIGHT; j++) {
        if (i > 0 && (GRID[i][j].type == FLUID || GRID[i - 1][j].type == FLUID))
        {
            if (GRID[i][j].type == SOLID || GRID[i - 1][j].type == SOLID)
                GRID_U[i][j].val = 0;
            else
                GRID_U[i][j].val -= scale * (GRID[i][j].pressure - GRID[i - 1][j].pressure);
        }
        if (j > 0 && (GRID[i][j].type == FLUID || GRID[i][j - 1].type == FLUID))
        {
            if (GRID[i][j].type == SOLID || GRID[i][j - 1].type == SOLID)
                GRID_V[i][j].val = 0;
            else
                GRID_V[i][j].val -= scale * (GRID[i][j].pressure - GRID[i][j - 1].pressure);
        }
    }
}

void Pressurer::solve_pressure(void) {
    (void)GRID_U;
    (void)GRID_V;
}
