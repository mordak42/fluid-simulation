
#ifndef __GRAVITER_HPP__
# define __GRAVITER_HPP__

#define GRAVITY_FACTOR 2

#include <iostream>
#include <memory>

#include "physicItems.hpp"
#include "physicLaw.hpp"

namespace mod1
{
class Graviter : public virtual PhysicLaw, public virtual PhysicItems
{
public:
     Graviter();
    ~Graviter();
    void solve_pressure(void);
    void update_velocity(void);
    void applyGravity();
private:
};
}

#endif
