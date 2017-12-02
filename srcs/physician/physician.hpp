
#ifndef __PHYSICIAN_HPP__
# define __PHYSICIAN_HPP__

#include <iostream>
#include <stdio.h>
#include "pressurer.hpp"
#include "physicLaw.hpp"
#include "graviter.hpp"
#include <mod1.hpp>

#define auto_init(variable, value) std::decay<decltype(value)>::type variable = value

#define PIC 0.95
#define FLIP 1 - PIC

/*
 * up = PIC * interp(ugrid, xp) + FLIP * (up + interp(∆u_grid)
 */

namespace mod1
{
class Physician : public Graviter, public Pressurer
{
public:
    Physician(struct particle *particles, struct cell *grid[MATH_HEIGHT]);
    ~Physician();
    void init_particules();
    void get_velocity_from_the_grid();
    void put_velocity_on_grid();
    void pic(int i, int j);
    void flip(int i, int j);
	void advect();
    struct cell **m_grid;
    std::unique_ptr<Pressurer> m_pressurer = nullptr;
private:
    struct particle *m_particles;
	double kernel(double x, double y);
	double hat(double r);
	double b_spline(double r);
};
}

#endif
