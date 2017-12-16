
#include "graviter.hpp"

namespace mod1
{

Graviter::Graviter() {};
    
#define G (GRAVITY_FACTOR * 9.81)

void Graviter::applyGravity() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            if (GRID_V[i][j].weight > 0) {
                GRID_V[i][j].val += -(G * DT);
            }
        }
    }
}

Graviter::~Graviter() {
}

}
