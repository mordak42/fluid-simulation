
#ifndef __PHYSIC_ITEMS_HPP__
# define __PHYSIC_ITEMS_HPP__
#include "../renderer/renderedFrame.hpp"
/* Ugly maccro definitions */
#define GRID m_physicItems->m_grid
#define PARTICLES m_physicItems->m_particles
#define GRID_U m_physicItems->m_grid_u
#define GRID_V m_physicItems->m_grid_v

/* Grid values for Physician part */
# define GRID_WIDTH 200
# define GRID_HEIGHT 200
# define GRID_SIZE (GRID_WIDTH) * (GRID_HEIGHT)
# define NB_PARTICLES 3600

# define DENSITY 9

/* Realism Number of meters */
# define REAL_WIDTH 20
# define REAL_HEIGHT 20


const double grid_width = GRID_WIDTH;
const double grid_height = GRID_HEIGHT;
const double grid_size = (grid_width) * (grid_height);

const double real_width = REAL_WIDTH;
const double real_height = REAL_HEIGHT;
const double frame_width = FRAME_WIDTH;
const double frame_height = FRAME_HEIGHT;

# define DX (real_width / grid_width)
# define DY (DX)

# define DT 0.04

# define GRID_TO_REAL(x) ((double)x / grid_width * real_width)
# define REAL_TO_GRID(x) ((double)x / real_width * grid_width)
# define FRAME_TO_GRID_WIDTH(x) ((double)x / frame_width * grid_width)
# define FRAME_TO_GRID_HEIGHT(x) (GRID_HEIGHT - 1 - (double)x / frame_height * grid_height)
# define GRID_TO_FRAME(x, y) ((double)x * frame_width / grid_width + y * frame_height / grid_height * frame_width)
# define REAL_TO_FRAME(x, y) ((double)x * frame_width / real_width + y * frame_height / grid_height * frame_width)

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
    struct cell m_grid[GRID_WIDTH][GRID_HEIGHT];
    struct particle m_particles[NB_PARTICLES];
    struct velocity_field m_grid_u[GRID_WIDTH + 1][GRID_HEIGHT];
    struct velocity_field m_grid_v[GRID_WIDTH][GRID_HEIGHT + 1];
};
}

#endif
