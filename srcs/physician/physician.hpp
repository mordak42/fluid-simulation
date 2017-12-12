
#ifndef __PHYSICIAN_HPP__
# define __PHYSICIAN_HPP__

#include <iostream>

#include "pressurer.hpp"
#include "physicLaw.hpp"
#include "graviter.hpp"
#include "physicItems.hpp"
/
#define PIC 0.50
#define FLIP (1.0 - PIC)

/*
 * up = PIC * interpolation(ugrid, xp) + FLIP * (up + interpolation(∆u_grid)
 */

namespace mod1
{
class Physician : public Graviter, public Pressurer

{
public:
    Physician();
    ~Physician();
    uint32_t init_particules(uint32_t ox, uint32_t oy, uint32_t width, uint32_t height, bool randomize);
    void get_velocity_from_the_grid();
    void put_velocity_on_grid();
    void flip(int i, int j);
	void advect();

private:
    void evaluateGridVelocityForParticle(vector3d position, vector3d velocity);
    void evaluateGridComponentVelocity(vector3d position, vector3d velocity, vector3d gridOffset, char field);
	double kernel(double x, double y);
	double hat(double r);
	double b_spline(double r);
	double evaluateComponentVelocity(vector3d position, vector3d gridOffset, char field, char method);
	double cubicInterpolate(double p[4], double x);
	double	 bicubicInterpolate(double p[4][4], double x, double y);
	vector3d evaluateVelocityAtPosition(vector3d position, char method);
};
}

#endif
