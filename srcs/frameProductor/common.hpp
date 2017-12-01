#ifndef __COMMON_HPP__
# define __COMMON_HPP__

# define MATH_WIDTH 1000
# define MATH_HEIGHT 2000
# define MATH_SIZE (MATH_WIDTH) * (MATH_HEIGHT)

/* Correspond au nombre de metres */

enum material_type
{
    SOLID,
    FLUID,
    AIR,
};

struct velocity_field
{
    double  weight;
    double  sum;
    double  val;
};

struct cell
{
    double              pressure;
    enum material_type  type;
};

const double REAL_SIZE = 10.0;

const double DX = REAL_SIZE / MATH_WIDTH;

const double DY = DX;

#define DT 0.04

#define REAL_SIZE_TO_GRID(x) x / REAL_SIZE * MATH_WIDTH

#endif
