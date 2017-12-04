
#ifndef __PHYSICIAN_HPP__
# define __PHYSICIAN_HPP__

#include <iostream>

#include "pressurer.hpp"
#include "physicLaw.hpp"
#include "graviter.hpp"
#include "physicItems.hpp"

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
    Physician(const std::shared_ptr<PhysicItems> &physicItems);
    ~Physician();
    int init_particules(int ox, int oy, int width, int height);
    void get_velocity_from_the_grid();
    void put_velocity_on_grid();
    void pic(int i, int j);
    void flip(int i, int j);
	void advect();

private:
	double kernel(double x, double y);
	double hat(double r);
	double b_spline(double r);
    std::unique_ptr<Pressurer> m_pressurer = nullptr;
    const std::shared_ptr<PhysicItems> &m_physicItems;
};
}

#endif
