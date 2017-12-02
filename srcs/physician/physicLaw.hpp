#ifndef __PHYSIC_LAW_HPP__
# define __PHYSIC_LAW_HPP__

#include <iostream>
#include <mod1.hpp>

#define auto_init(variable, value) std::decay<decltype(value)>::type variable = value

namespace mod1
{
class PhysicLaw
{
public:
    PhysicLaw();
    ~PhysicLaw();

protected:
    auto_init(m_grid_u, new struct velocity_field[MATH_WIDTH + 1][MATH_HEIGHT]);
    auto_init(m_grid_v, new struct velocity_field[MATH_WIDTH][MATH_HEIGHT + 1]);
};
}

#endif
