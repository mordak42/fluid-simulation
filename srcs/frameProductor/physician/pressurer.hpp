
#ifndef __PRESSURER_HPP__
# define __PRESSURER_HPP__

#include <iostream>
#include <stdio.h>
#include "common.hpp"

#define auto_init(variable, value) std::decay<decltype(value)>::type variable = value

namespace mod1
{
class Pressurer
{
public:
    Pressurer(struct velocity_field **grid_u,
                     struct velocity_field **grid_v, struct cell **grid);
    ~Pressurer();
    void solve_pressure(void);
	void update_velocity(void);
private:
    struct velocity_field **m_grid_u;
    struct velocity_field **m_grid_v;
	struct cell **m_grid;
};
}

#endif
