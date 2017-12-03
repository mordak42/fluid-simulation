
#include "physician/physicItems.hpp"

using namespace mod1;

PhysicItems::PhysicItems() {
    for (int i = 0; i < MATH_WIDTH; i++)
        m_grid[i].fill((struct cell){0, SOLID});
}

PhysicItems::~PhysicItems() {}
