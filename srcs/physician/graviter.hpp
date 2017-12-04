
#ifndef __GRAVITER_HPP__
# define __GRAVITER_HPP__

#include <iostream>
#include <memory>

#include "physicItems.hpp"
#include "physicLaw.hpp"

namespace mod1
{
class Graviter : public virtual PhysicLaw
{
public:
    Graviter(const std::shared_ptr<PhysicItems> &physicItems);
    ~Graviter();
    void solve_pressure(void);
	void update_velocity(void);
    void applyGravity();
private:
    const std::shared_ptr<PhysicItems> &m_physicItems;
};
}

#endif
