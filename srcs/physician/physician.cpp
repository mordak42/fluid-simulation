
#include "physician.hpp"

using namespace mod1;

Physician::Physician(const std::shared_ptr<PhysicItems> &physicItems) :
                        PhysicLaw(),
                        Graviter(physicItems),
                        Pressurer(physicItems),
                        m_physicItems(physicItems)
{}

Physician::~Physician() {}



/*
 * function hat(r) = 1 - r if ( 0 <= r <= 1)
 *                  1 + r if ( -1 <= r <= 0)
 *                  0 else
 */

double Physician::hat(double r) {
    if (0 <= r && r <= 1)
        return (1 - r);
    else if (-1 <= r && r <= 0)
        return (1 + r);
    else
    {
        //std::cerr << "bad input for function hat ?" << std::endl;
        return 0;
    }
}

/*
 * function b_spline(r) =
 *      1 / 2 (r + 3 / 2) ^ 2 if -3 / 2 <= r < -1 / 2
 *      3 / 4 - r^2           if -1 / 2 <= r < 1 / 2
 *      1 / 2 (3 / 2 - r) ^ 2 if 1 / 2 <= r < 3 / 2
 *      0                     else
 */

double Physician::b_spline(double r) {
    if (-1.5 <= r && r <= -0.5)
        return (0.5 * (r + 1.5) * (r + 1.5));
    else if (-0.5 <= r && r <= 0.5)
        return (0.75 - r * r);
    else if (0.5 <= r && r <= 1.5)
        return (0.5 * (1.5 - r) * (1.5 - r));
    else
    {
        std::cerr << "bad input for function b_spline ?" << std::endl;
        return 0;
    }
}

/*
 * function kernel(x,y,z) = hat(x/DX)*hat(y/DY)*hat(z/DZ)
 */

double Physician::kernel(double x, double y) {
    return (hat(x / DX) * hat(y / DY));
}

void Physician::put_velocity_on_grid() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
                GRID_U[i][j].sum = 0;
                GRID_V[i][j].sum = 0;
                GRID_U[i][j].weight = 0;
                GRID_V[i][j].weight = 0;
                GRID_V[i][j].val = 0;
                GRID_U[i][j].val = 0;
                if (GRID[i][j].type == FLUID)
                    GRID[i][j].type = AIR;
        }
    }
    for (int p = 0; p < NB_PARTICLES; p++) {
        /*
         * m_grid[i][j] is the case where the particle is
         * so the particle velocity contribute to
         * m_grid_u[i][j] and m_grid_v[i + 1][j]
         *
         *             j + 1  _______________
         *                    |             |
         *                    |  .          |
         *      j + 0.5 * DY  |.   i,j      |
         *                    |             |
         *                    |    .        |
         *              j     ---------------
         *                   i *dx         (i + 1)*dx
         *
         *  the distance for the velocity grid :
         *  grid_u[i][j] = (i * dx , j * dy)
         *  the distance for the pressure grid :
         *  grid_p[i][j] = ((i + 0.5) * dx , (j + 0.5) * dy)
         *
         *  m_grid_u[i][j] = ∑ (k(xp - i * dx)up / ∑(k(xp - i * dx)
         *
         *
         */
        double x = PARTICLES[p].x;
        double y = PARTICLES[p].y;
        double up = PARTICLES[p].u;
        double vp = PARTICLES[p].v;

        int i = x / DX;
        int j = y / DY;
        if (GRID[i][j].type == AIR)
            GRID[i][j].type = FLUID;
        //TODO: update also m_grid_u[i - 1]


        GRID_U[i][j].sum        += kernel(x - i * DX, y - (j + 0.5) * DY) * up;
        GRID_U[i + 1][j].sum    += kernel(x - (i + 1) * DX, y - (j + 0.5) * DY) * up;

        GRID_V[i][j].sum        += kernel(x - (i + 0.5) * DX, y - j * DY) * vp;
        GRID_V[i][j + 1].sum    += kernel(x - (i + 0.5) * DX, y - (j + 1) * DY) * vp;

        GRID_U[i][j].weight     += kernel(x - i * DX, y - (j + 0.5) * DY);
        GRID_U[i + 1][j].weight += kernel(x - (i + 1) * DX, y - (j + 0.5) * DY);

        GRID_V[i][j].weight     += kernel(x - (i + 0.5) * DX, y - j * DY);
        GRID_V[i][j + 1].weight += kernel(x - (i + 0.5) * DX, y - (j + 1) * DY);
    }
    for (int i = 0; i < GRID_WIDTH + 1; i++) {
        for (int j = 0; j < GRID_HEIGHT + 1; j++) {
            if (j < GRID_HEIGHT && GRID_U[i][j].weight)
                GRID_U[i][j].val = GRID_U[i][j].sum / GRID_U[i][j].weight;
            if (i < GRID_WIDTH && GRID_V[i][j].weight)
                GRID_V[i][j].val = GRID_V[i][j].sum / GRID_V[i][j].weight;
        }
    }
}
void Physician::pic(int i, int j) {
    (void)i;
    (void)j;
}

void Physician::flip(int i, int j) {

    (void)i;
    (void)j;
}

void Physician::get_velocity_from_the_grid() {
    for (int p = 0; p < NB_PARTICLES; p++) {
        double x = PARTICLES[p].x;
        double y = PARTICLES[p].y;

        int i = x / DX;
        int j = y / DY;

		/*
         *
         *             j + 1  _______________
         *                    |             |
         *                    |  .          |
         *      j + 0.5 * DY  |.   i,j      |
         *                    |             |
         *                    |    .        |
         *              j     ---------------
         *                   i *dx         (i + 1)*dx
         *
		 */
		/* update u coordinate */
		double sum = 0;
		double weight = 0;

		sum += kernel(x - i * DX, y - (j + 0.5) * DY) * GRID_U[i][j].val;
		sum += kernel(x - (i + 1) * DX, y - (j + 0.5) * DY) * GRID_U[i + 1][j].val;
		weight += kernel(x - i * DX, y - (j + 0.5) * DY);
		weight += kernel(x - (i + 1) * DX, y - (j + 0.5) * DY);

		PARTICLES[p].u = sum / weight;

		/* update v coordinate */
		sum = 0;
		weight = 0;

		sum += kernel(x - (i + 0.5) * DX, y - j * DY) * GRID_V[i][j].val;
		sum += kernel(x - (i + 0.5) * DX, y - (j + 1) * DY) * GRID_V[i][j + 1].val;
		weight += kernel(x - (i + 0.5) * DX, y - j * DY);
		weight += kernel(x - (i + 0.5) * DX, y - (j + 1) * DY);

		PARTICLES[p].v = sum / weight;
    }
}

int Physician::init_particules(int ox, int oy, int width, int height) {
    int nb_particles = width * height * DENSITY_RACINE * DENSITY_RACINE;
    for (int i = 0; i < nb_particles; i++) {
        PARTICLES[i].x = ((double)ox + ((double)(i % (width * DENSITY_RACINE)) / DENSITY_RACINE)) * DX;
        PARTICLES[i].y = ((double)oy - ((double)(i / (width * DENSITY_RACINE)) / DENSITY_RACINE)) * DY;
        PARTICLES[i].v = 0;
        PARTICLES[i].u = 0;
    }
    return nb_particles;
}

void Physician::advect() {
    for (int p = 0; p < NB_PARTICLES; p++) {
        PARTICLES[p].x += PARTICLES[p].u * DT;
        PARTICLES[p].y += PARTICLES[p].v * DT;
    }
}
