
#ifndef __PHYSICIAN_HPP__
# define __PHYSICIAN_HPP__

#include <iostream>
#include <stdio.h>
#include "common.hpp"

#define auto_init(variable, value) std::decay<decltype(value)>::type variable = value

#define PIC 0.95
#define FLIP 1 - PIC

#define NB_PARTICLES 1000
#define DT 0.04
/*
 * up = PIC * interp(ugrid, xp) + FLIP * (up + interp(∆u_grid)
 */

struct velocity_field
{
    double  weight;
    double  sum;
    double  val;
};

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
	Physician(struct particle *particles);
	double kernel(double x, double y);
	double hat(double r);
	double b_spline(double r);
	void advect();
	void put_particle_on_grid();
    ~Physician();
    auto_init(m_grid_u, new struct velocity_field[MATH_HEIGHT][MATH_WIDTH + 1]);
    auto_init(m_grid_v, new struct velocity_field[MATH_HEIGHT + 1][MATH_WIDTH]);
private:
    struct particle *m_particles;
};
}

#endif
