
#include "graviter.hpp"

namespace mod1
{

Graviter::Graviter() {};
    
#define G 9.81

/*
                g = (Vx - GRID_V[i][j]) / DT;
                Vx - GRID_V[i][j] = g * DT;
                Vx = (g * DT) + GRID_V[i][j];
*/

void Graviter::applyGravity() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            if (GRID_V[i][j].weight > 0) {
                GRID_V[i][j].val = -(G * DT) + GRID_V[i][j].val;
            }
        }
    }
}

Graviter::~Graviter() {
}

}
