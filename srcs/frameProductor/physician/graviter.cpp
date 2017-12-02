#include "graviter.hpp"

namespace mod1
{

Graviter::Graviter(struct cell **grid)
                     : PhysicLaw(), m_grid(grid) {}

Graviter::~Graviter() {
}

}

