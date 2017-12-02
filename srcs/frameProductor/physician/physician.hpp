
#ifndef __PHYSICIAN_HPP__
# define __PHYSICIAN_HPP__

#include <iostream>
#include <stdio.h>
#include "common.hpp"
#include "pressurer.hpp"

#define auto_init(variable, value) std::decay<decltype(value)>::type variable = value

#define PIC 0.95
#define FLIP 1 - PIC

#define NB_PARTICLES 1000
/*
 * up = PIC * interp(ugrid, xp) + FLIP * (up + interp(∆u_grid)
 */

struct particle
{
    double u;
    double v;
    double x;
    double y;
};

namespace mod1
{
class Physician
{
public:
    Physician(struct particle *particles, struct cell *grid[MATH_HEIGHT]);
    ~Physician();
	double kernel(double x, double y);
	double hat(double r);
	double b_spline(double r);
    void init_particules();
    void get_velocity_from_the_grid();
    void put_velocity_on_grid();
    void pic(int i, int j);
    void flip(int i, int j);
	void advect();
    auto_init(m_grid_u, new struct velocity_field[MATH_WIDTH + 1][MATH_HEIGHT]);
    auto_init(m_grid_v, new struct velocity_field[MATH_WIDTH][MATH_HEIGHT + 1]);
    std::unique_ptr<Pressurer> m_pressurer = nullptr;
	struct cell **m_grid;
    struct particle *m_particles;
private:
};
}

#endif
