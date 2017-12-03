
#ifndef __GRAVITER_HPP__
# define __GRAVITER_HPP__

#include <iostream>
#include <stdio.h>

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
private:
    const std::shared_ptr<PhysicItems> &m_physicItems;
};
}

#endif
