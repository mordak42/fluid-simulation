#include "graviter.hpp"

namespace mod1
{

Graviter::Graviter(const std::shared_ptr<PhysicItems> &physicItems) :
                                                    PhysicLaw(),
                                                    m_physicItems(physicItems)
{

}

Graviter::~Graviter() {
}

}
