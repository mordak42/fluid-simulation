#include "physician.hpp"

namespace mod1
{

Physician::Physician(struct particle *particles) : m_particles(particles) {}

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
    if (-3/2 <= r && r <= -1/2)
        return (1/2 * (r + 3/2) * (r + 3/2));
    else if (-1/2 <= r && r <= 1/2)
        return (3/4 - r * r);
    else if (1/2 <= r && r <= 3/2)
        return (1/2 * (3 / 2 - r) * (3 / 2 - r));
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

void Physician::put_particle_on_grid() {
    double x = m_particles[0].x;
    x = x + 1;
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

        m_grid_u[i][j].sum            += kernel(x - i * DX, y - (j + 0.5) * DY) * up;
        m_grid_u[i + 1][j].sum        += kernel(x - i * DX, y - (j + 0.5) * DY) * up;

        m_grid_v[i][j].sum            += kernel(x - (i + 0.5) * DX, y - j * DY) * vp;
        m_grid_v[i][j + 1].sum        += kernel(x - (i + 0.5) * DX, y - j * DY) * vp;

        m_grid_u[i][j].weight         += kernel(x - i * DX, y - (j + 0.5) * DY);
        m_grid_u[i + 1][j].weight     += kernel(x - i * DX, y - (j + 0.5) * DY);

        m_grid_v[i][j].weight         += kernel(x - (i + 0.5) * DX, y - j * DY);
        m_grid_v[i][j + 1].weight     += kernel(x - (i + 0.5) * DX, y - j * DY);
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

void Physician::init_particules() {
    //TODO: error essay de faire un carre
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            m_particles[i + j].x = i * DX;
            m_particles[i + j].y = MATH_HEIGHT - j * DY;
            m_particles[i + j].u = 1;
            m_particles[i + j].v = 1;
        }
    }
}

void Physician::advect() {
    for (int p = 0; p < NB_PARTICLES; p++) {
        m_particles[p].x += m_particles[p].u * DT;
        m_particles[p].y += m_particles[p].v * DT;
    }
}
}