
#ifndef __PHYSICIAN_HPP__
# define __PHYSICIAN_HPP__

#include <iostream>

#include "pressurer.hpp"
#include "physicLaw.hpp"
#include "graviter.hpp"
#include "physicItems.hpp"

#define PIC 0.05
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
    uint32_t initParticules(uint32_t ox, uint32_t oy, uint32_t width, uint32_t height, bool randomize);
    void get_velocity_from_the_grid();
    void put_velocity_on_grid();
    void flip(int i, int j);
	void advect();
	void bzeroVelocity();
	void saveVelocity();
	void extrapolateVelocity();
    void updateGridLabel();
    void pluieDiluvienne();
    void femmeFontaine(uint32_t ox, uint32_t oy, float vel);

private:
	float kernel(vector3d v);
	float hat(float r);
	void evaluateGridComponentVelocity(vector3d position,
			vector3d velocity,
			vector3d gridOffset,
			int      gi,
			int      gj,
			char field);
	void evaluateGridVelocityAtPosition(vector3d position,
			vector3d velocity,
			int gi,
			int gj,
			char field);
	float b_spline(float r);
	float evaluateComponentVelocity(vector3d position, vector3d gridOffset, char field, char method);
	float cubicInterpolate(float p[4], float x);
	float	 bicubicInterpolate(float p[4][4], float x, float y);
	vector3d evaluateVelocityAtPosition(vector3d position, char method);
	float moyU(int i, int j);
	float moyV(int i, int j);
};
}

#endif
