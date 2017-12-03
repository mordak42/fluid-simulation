
#ifndef __PHYSIC_ITEMS_HPP__
# define __PHYSIC_ITEMS_HPP__

/* Ugly maccro definitions */
#define GRID m_physicItems->m_grid
#define PARTICLES m_physicItems->m_particles
#define GRID_U m_physicItems->m_grid_u
#define GRID_V m_physicItems->m_grid_v

/* Grid values for Physician part */
# define MATH_WIDTH 200
# define MATH_HEIGHT 100
# define MATH_SIZE (MATH_WIDTH) * (MATH_HEIGHT)
# define NB_PARTICLES 1000

/* Realism Number of meters */
const double REAL_SIZE = 10.0;

const double DX = REAL_SIZE / MATH_WIDTH;
const double DY = DX;

# define DT 0.04

# define REAL_SIZE_TO_GRID(x) x / REAL_SIZE * MATH_WIDTH

namespace mod1
{
struct velocity_field
{
    double  weight;
    double  sum;
    double  val;
};

enum material_type
{
    SOLID,
    FLUID,
    AIR,
};

struct particle
{
    double u;
    double v;
    double x;
    double y;
};

struct cell
{
    double              pressure;
    enum material_type  type;
};

class PhysicItems
{
public:
    PhysicItems();
    ~PhysicItems();
    struct cell m_grid[MATH_WIDTH][MATH_HEIGHT];
    struct particle m_particles[NB_PARTICLES];
    struct velocity_field m_grid_u[MATH_WIDTH + 1][MATH_HEIGHT];
    struct velocity_field m_grid_v[MATH_WIDTH][MATH_HEIGHT + 1];
};
}

#endif
