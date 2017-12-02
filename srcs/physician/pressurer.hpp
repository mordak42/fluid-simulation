
#ifndef __PRESSURER_HPP__
# define __PRESSURER_HPP__

#include <iostream>
#include <stdio.h>
#include <mod1.hpp>
#include "physicLaw.hpp"

#define auto_init(variable, value) std::decay<decltype(value)>::type variable = value

namespace mod1
{
class Pressurer : public virtual PhysicLaw
{
public:
    Pressurer(struct cell **grid);
    ~Pressurer();
    void solve_pressure(void);
	void update_velocity(void);
private:
	struct cell **m_grid;
};
}

#endif
