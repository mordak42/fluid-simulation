
#ifndef __PHYSIC_ITEMS_HPP__
# define __PHYSIC_ITEMS_HPP__

#include "../renderer/renderedFrame.hpp"

#include <vector>

/* Ugly macro definitions */
#define GRID m_grid
#define PARTICLES m_particles
#define GRID_U m_grid_u
#define GRID_V m_grid_v

/* Grid values for Physician part */
# define GRID_WIDTH 256
# define GRID_HEIGHT 256
# define GRID_SIZE (GRID_WIDTH) * (GRID_HEIGHT)

# define DENSITY_RACINE 2

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

/* Time interval between two displayed frames */
# define DT 0.04

namespace mod1
{
    struct vector3d
    {
        double x, y, z;

        inline vector3d( void ) {}
        inline vector3d( const double X, const double Y, const double Z )
        { x = X; y = Y; z = Z; }

        inline vector3d operator + (const vector3d& A) const
        { return vector3d( x + A.x, y + A.y, z + A.z ); }

        inline std::string operator << (const vector3d& A) const
        { return "x: " + std::to_string(A.x) + "\ny: " + std::to_string(A.y) + "\n";}

        void operator+=(const vector3d& A)
        { x += A.x; y += A.y; z += A.z; }

        void operator-=(const vector3d& A)
        {  x -= A.x; y -= A.y; z -= A.z; }

        inline vector3d operator - (const vector3d& A) const
        { return vector3d( x - A.x, y - A.y, z - A.z ); }

        inline vector3d operator + (const double A) const
        { return vector3d( x + A, y + A, z + A ); }

        inline vector3d operator * (const double A) const
        { return vector3d( x * A, y * A, z * A ); }

        inline vector3d operator / (const double A) const
        { return vector3d( x / A, y / A, z / A ); }

        inline vector3d operator - ( const double A ) const
        { return vector3d( x - A, y - A, z - A ); }

        inline double Dot(const vector3d& A) const
        { return A.x*x + A.y*y + A.z*z; }
    };

    struct velocity_field
    {
        float  weight;
        float  sum;
        float  val;
        float  oldVal;
    };

    enum material_type
    {
        SOLID,
        FLUID,
        AIR,
        SURROUND,
    };

    struct particle
    {
        vector3d vel;
        vector3d pos;
    };

    struct cell
    {
        enum material_type  type;
    };

    class PhysicItems
    {
        public:
            PhysicItems();
            ~PhysicItems();
            struct cell m_grid[GRID_WIDTH][GRID_HEIGHT];
            struct velocity_field m_grid_u[GRID_WIDTH + 1][GRID_HEIGHT];
            struct velocity_field m_grid_v[GRID_WIDTH][GRID_HEIGHT + 1];
            std::vector<struct particle> m_particles;

        protected:
            std::string parseClFile(const char *filename);
            void serializeGridV(
                    struct velocity_field (&dst)[GRID_WIDTH * (GRID_HEIGHT + 1)],
                    struct velocity_field (&grid_v)[GRID_WIDTH][GRID_HEIGHT + 1]);
            void unserializeGridV(
                    struct velocity_field (&grid_v)[GRID_WIDTH][GRID_HEIGHT + 1],
                    struct velocity_field (&src)[GRID_WIDTH * (GRID_HEIGHT + 1)]);
    };
}

#endif
