
#include "physician.hpp"

namespace mod1
{

Physician::Physician(const std::shared_ptr<mod1::Pool> &pool) : m_pool(pool) {
}

Physician::~Physician() {}
}
