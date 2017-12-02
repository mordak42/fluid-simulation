#include "physician.hpp"

namespace mod1
{

Physician::Physician(struct particle *particles, struct cell **grid)
                    : m_grid(grid),
					  m_particles(particles)
{
    m_pressurer.reset(new Pressurer((struct velocity_field **)m_grid_u,
									(struct velocity_field **)m_grid_v,
									grid));
}

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
        printf("bad input for function hat ?\n");
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
        printf("bad input for function b_spline ?\n");
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
        double x = m_particles[p].x;
        double y = m_particles[p].y;
        double up = m_particles[p].u;
        double vp = m_particles[p].v;

        int i = x / DX;
        int j = y / DY;

        //TODO: update also m_grid_u[i - 1]

        m_grid_u[i][j].sum        += kernel(x - i * DX, y - (j + 0.5) * DY) * up;
        m_grid_u[i + 1][j].sum    += kernel(x - (i + 1) * DX, y - (j + 0.5) * DY) * up;

        m_grid_v[i][j].sum        += kernel(x - (i + 0.5) * DX, y - j * DY) * vp;
        m_grid_v[i][j + 1].sum    += kernel(x - (i + 0.5) * DX, y - (j + 1) * DY) * vp;

        m_grid_u[i][j].weight     += kernel(x - i * DX, y - (j + 0.5) * DY);
        m_grid_u[i + 1][j].weight += kernel(x - (i + 1) * DX, y - (j + 0.5) * DY);

        m_grid_v[i][j].weight     += kernel(x - (i + 0.5) * DX, y - j * DY);
        m_grid_v[i][j + 1].weight += kernel(x - (i + 0.5) * DX, y - (j + 1) * DY);
    }
    for (int i = 0; i < MATH_WIDTH + 1; i++) {
        for (int j = 0; j < MATH_HEIGHT + 1; j++) {
            if (j < MATH_HEIGHT && m_grid_u[i][j].weight)
                m_grid_u[i][j].val = m_grid_u[i][j].sum / m_grid_u[i][j].weight;
            if (i < MATH_WIDTH && m_grid_v[i][j].weight)
                m_grid_v[i][j].val = m_grid_v[i][j].sum / m_grid_v[i][j].weight;
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
        double x = m_particles[p].x;
        double y = m_particles[p].y;

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
		/* udatte u coord */
		double sum = 0;
		double weight = 0;

		sum += kernel(x - i * DX, y - (j + 0.5) * DY) * m_grid_u[i][j].val;
		sum += kernel(x - (i + 1) * DX, y - (j + 0.5) * DY) * m_grid_u[i + 1][j].val;
		weight += kernel(x - i * DX, y - (j + 0.5) * DY);
		weight += kernel(x - (i + 1) * DX, y - (j + 0.5) * DY);

		m_particles[p].u = sum / weight;

		/* udatte v coord */
		sum = 0;
		weight = 0;

		sum += kernel(x - (i + 0.5) * DX, y - j * DY) * m_grid_v[i][j].val;
		sum += kernel(x - (i + 0.5) * DX, y - (j + 1) * DY) * m_grid_v[i][j + 1].val;
		weight += kernel(x - (i + 0.5) * DX, y - j * DY);
		weight += kernel(x - (i + 0.5) * DX, y - (j + 1) * DY);

		m_particles[p].v = sum / weight;
    }
}

void Physician::init_particules() {
    for (int i = 0; i < 1000; i++) {
        m_particles[i].x = i / 333 * DX + DX / 2;
        m_particles[i].y = (MATH_HEIGHT - (i % 333) - 0.5) * DY;
        m_particles[i].u = 0;
        m_particles[i].v = -1;
    }
}

void Physician::advect() {
    for (int p = 0; p < NB_PARTICLES; p++) {
        m_particles[p].x += m_particles[p].u * DT;
        m_particles[p].y += m_particles[p].v * DT;
    }
}
}
