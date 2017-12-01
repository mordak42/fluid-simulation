
#ifndef __MOD1_HPP__
# define __MOD1_HPP__

/* Grid values for Physician part */
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


namespace mod1
{

class Mod1Implementation;

class Mod1
{
public:
    Mod1();
    ~Mod1();

    void run();
    void stop();

private:
    std::unique_ptr<Mod1Implementation> m_implementation;
};
}

#endif
