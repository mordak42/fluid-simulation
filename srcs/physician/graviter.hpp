
#ifndef __GRAVITER_HPP__
# define __GRAVITER_HPP__

#include <iostream>
#include <stdio.h>
#include <mod1.hpp>
#include "physicLaw.hpp"

#define auto_init(variable, value) std::decay<decltype(value)>::type variable = value

namespace mod1
{
class Graviter : public virtual PhysicLaw
{
public:
    Graviter(struct cell **grid);
    ~Graviter();
    void solve_pressure(void);
	void update_velocity(void);
private:
	struct cell **m_grid;
};
}

#endif
