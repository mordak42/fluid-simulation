
#include "graviter.hpp"

namespace mod1
{

Graviter::Graviter(const std::shared_ptr<PhysicItems> &physicItems) :
                                                    PhysicLaw(),
                                                    m_physicItems(physicItems)
{
}

#define G 9.81

void Graviter::applyGravity() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
                /* check below class no work with vidange */
            if (GRID_V[i][j].weight > 0) {
/*
                g = (Vx - GRID_V[i][j]) / DT;
                Vx - GRID_V[i][j] = g * DT;
                Vx = (g * DT) + GRID_V[i][j];
*/
                GRID_V[i][j].val = -(G * DT) + GRID_V[i][j].val;
            }
        }
    }
}

Graviter::~Graviter() {
}

}
