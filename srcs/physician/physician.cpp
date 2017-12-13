
#include "physician.hpp"

#include <ctime>

using namespace mod1;

Physician::Physician(){};

Physician::~Physician() {}

void Physician::bzeroVelocity() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            GRID_U[i][j].sum = 0;
            GRID_V[i][j].sum = 0;
            GRID_U[i][j].weight = 0;
            GRID_V[i][j].weight = 0;
            GRID_U[i][j].oldVal = 0;
            GRID_V[i][j].oldVal = 0;
            GRID_V[i][j].val = 0;
            GRID_U[i][j].val = 0;
        }
    }
}

void Physician::saveVelocity() {
    for (int i = 0; i < GRID_WIDTH; i++)
        for (int j = 0; j < GRID_HEIGHT; j++) {
            GRID_U[i][j].oldVal = 0;
            GRID_V[i][j].oldVal = 0;
        }
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            GRID_U[i][j].oldVal = GRID_U[i][j].val;
            GRID_V[i][j].oldVal = GRID_V[i][j].val;
        }
    }
}

/*
 *                        GRID_V[i][j+1]
 *                    _______________
 *                    |             |
 *                    |  .          |
 *     GRID_U[i][j]   |.   i,j      | GRID_U[i+1][j]
 *                    |             |
 *                    |    .        |
 *                    ---------------
 *                      GRID_V[i][j] 
 *
 */

void Physician::extrapolateVelocity()
{
    for (int i = 1; i < GRID_WIDTH - 1; i++) {
        for (int j = 1; j < GRID_HEIGHT - 1; j++) {
            if (GRID[i][j].type == AIR && (GRID[i][j + 1].type == FLUID
                        || GRID[i + 1][j].type == FLUID
                        || GRID[i - 1][j].type == FLUID
                        || GRID[i][j - 1].type == FLUID))
            {
                GRID_U[i][j].weight = 1;
                GRID_V[i][j].weight = 1;
                if (GRID_U[i][j].val == 0)
                    GRID_U[i][j].val = GRID_U[i + 1][j].val;
                if (GRID_U[i + 1][j].val == 0)
                    GRID_U[i + 1][j].val = GRID_U[i][j].val;
                if (GRID_V[i][j].val == 0)
                    GRID_V[i][j].val = GRID_V[i][j + 1].val;
                if (GRID_V[i][j + 1].val == 0)
                    GRID_V[i][j + 1].val = GRID_V[i][j].val;
            }
        }
    }
}

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
        // std::cerr << "bad input for function b_spline ?" << std::endl;
        return 0;
    }
}

/*
 * function kernel(x,y,z) = hat(x/DX)*hat(y/DY)*hat(z/DZ)
 */

double Physician::kernel(vector3d v) {
    return (b_spline(v.x / DX) * b_spline(v.y / DY));
}

void Physician::evaluateGridComponentVelocity(vector3d position,
        vector3d velocity,
        vector3d gridOffset,
        int      gi,
        int      gj,
        char field)
{
    vector3d gpos = vector3d(gi, gj, 0) * DX;
    gpos += gridOffset;

    //std::cout << "grid component gi: " << gi;
    double kernelVal = kernel(position - gpos);
    if (field == 'u') {
        GRID_U[gi][gj].sum        += kernelVal * velocity.x;
        GRID_U[gi][gj].weight     += kernelVal;
    }
    else {
        GRID_V[gi][gj].sum        += kernelVal * velocity.y;
        GRID_V[gi][gj].weight     += kernelVal;
    }
}

void Physician::evaluateGridVelocityAtPosition(vector3d position,
        vector3d velocity,
        int gi,
        int gj,
        char field)
{
    double hdx = 0.5 * DX;
    vector3d offset;
    if (field == 'u')
        offset = vector3d(0.0, hdx, hdx);
    else
        offset = vector3d(hdx, 0.0, hdx);
    //vector3d offsetW(hdx, hdx, 0.0);

    evaluateGridComponentVelocity(position, velocity, offset, gi, gj, field);
}

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

void Physician::put_velocity_on_grid() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            GRID_U[i][j].sum = 0;
            GRID_V[i][j].sum = 0;
            GRID_U[i][j].weight = 0;
            GRID_V[i][j].weight = 0;
            //   GRID_U[i][j].oldVal = 0;
            //   GRID_V[i][j].oldVal = 0;
            GRID_V[i][j].val = 0;
            GRID_U[i][j].val = 0;
            if (GRID[i][j].type == FLUID)
                GRID[i][j].type = AIR;
        }
    }
    for (unsigned long int p = 0; p < PARTICLES.size(); p++) {
        //std::cout << "x"<<x <<"y" << y << "velx"<< up << "vely" << vp <<std::endl;

        int gi = PARTICLES[p].pos.x / DX;
        int gj = PARTICLES[p].pos.y / DY;
        if (gi < 0 || gi >= GRID_WIDTH)
            continue;
        if (gj < 0 || gj >= GRID_HEIGHT)
            continue;
        if (GRID[gi][gj].type == AIR)
            GRID[gi][gj].type = FLUID;

        vector3d pos = PARTICLES[p].pos;
        vector3d vel = PARTICLES[p].vel;

        evaluateGridVelocityAtPosition(pos, vel, gi, gj, 'u');
        evaluateGridVelocityAtPosition(pos, vel, gi + 1, gj, 'u');
        evaluateGridVelocityAtPosition(pos, vel, gi, gj, 'v');
        evaluateGridVelocityAtPosition(pos, vel, gi, gj + 1, 'v');
    }
    for (int i = 0; i < GRID_WIDTH + 1; i++) {
        for (int j = 0; j < GRID_HEIGHT + 1; j++) {
            if (j < GRID_HEIGHT && GRID_U[i][j].weight) {
                GRID_U[i][j].val = GRID_U[i][j].sum / GRID_U[i][j].weight;
                //      GRID_U[i][j].oldVal = GRID_U[i][j].val;
            }
            if (i < GRID_WIDTH && GRID_V[i][j].weight) {
                GRID_V[i][j].val = GRID_V[i][j].sum / GRID_V[i][j].weight;
                //      GRID_V[i][j].oldVal = GRID_V[i][j].val;
            }
        }
    }
}

double Physician::cubicInterpolate(double p[4], double x) {
    return p[1] + 0.5 * x*(p[2] - p[0] + 
            x*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + 
                x*(3.0*(p[1] - p[2]) + p[3] - p[0])));
}

double Physician::bicubicInterpolate(double p[4][4], double x, double y) {
    double arr[4];
    arr[0] = cubicInterpolate(p[0], y);
    arr[1] = cubicInterpolate(p[1], y);
    arr[2] = cubicInterpolate(p[2], y);
    arr[3] = cubicInterpolate(p[3], y);
    return cubicInterpolate(arr, x);
}

/*
 *         _________________________________________
 *         |           |             |             |
 *         |           |             |             |
 *         |           |  .          |             |
 *         |           |             |             |
 *         |           |             |             |
 *         _________________________________________
 *         |           |             |             |
 *         |           |             |             |
 *         |           |             |             |
 *         |           |             |             |
 *         |           |             |             |
 *         _________________________________________
 */
double Physician::evaluateComponentVelocity(vector3d position,
        vector3d gridOffset,
        char field, char method)
{
    int gi = position.x / DX;
    int gj = position.y / DX;
    double points[4][4];

    for (int j = 0; j < 4; j++) {
        int grid_j = j + gj - 1;
        for (int i = 0; i < 4; i++) {
            int grid_i = i + gi - 1;
            //std::cout << "get grdi_i: " << grid_i << std::endl;
            if (field == 'u')
            {
                if (method == 'p' && grid_i > 0 && grid_i < GRID_WIDTH + 1) /* PIC */
                    points[i][j] = GRID_U[grid_i][grid_j].val;
                else              /* FLIP */
                    points[i][j] = GRID_U[grid_i][grid_j].val - GRID_U[grid_i][grid_j].oldVal;
            }
            else
            {
                if (method == 'p' && grid_i > 0 && grid_i < GRID_WIDTH) 
                    points[i][j] = GRID_V[grid_i][grid_j].val;
                else
                    points[i][j] = GRID_V[grid_i][grid_j].val - GRID_V[grid_i][grid_j].oldVal;
            }
        }
    }
    vector3d gpos = vector3d(gi, gj, 0) * DX;
    gpos += gridOffset;
    (void)gridOffset;
    vector3d interp = (position - gpos) / DX;
    return bicubicInterpolate(points, interp.x, interp.y);
}

vector3d Physician::evaluateVelocityAtPosition(vector3d position, char method) {
    double hdx = 0.5 * DX;
    vector3d offsetU(0.0, hdx, hdx);
    vector3d offsetV(hdx, 0.0, hdx);
    //vector3d offsetW(hdx, hdx, 0.0);

    double vx = evaluateComponentVelocity(position, offsetU, 'u', method);
    double vy = evaluateComponentVelocity(position, offsetV, 'v', method);
    return vector3d(vx, vy, 0);
}

void Physician::get_velocity_from_the_grid() {
    for (unsigned long int p = 0; p < PARTICLES.size(); p++) {
        PARTICLES[p].vel = evaluateVelocityAtPosition(PARTICLES[p].pos, 'p') * PIC
            + ((PARTICLES[p].vel + evaluateVelocityAtPosition(PARTICLES[p].pos, 'f')) * FLIP);
    }
}

uint32_t Physician::init_particules(uint32_t ox, uint32_t oy, uint32_t width, uint32_t height, bool randomize) {
    if (ox + width >= GRID_WIDTH || oy + height >= GRID_HEIGHT) {
        std::cerr << "Some particles will be outside the grid: " << ox + width << " " << oy + height << " on " << GRID_WIDTH << "*" << GRID_HEIGHT << std::endl;
        return 0;
    }
    uint32_t nb_particles = width * height * DENSITY_RACINE * DENSITY_RACINE;
    if (nb_particles == 0) {
        std::cerr << "There are no particle to fill it" << std::endl;
        return 0;
    }
    std::srand(std::time(0));
    size_t offset = PARTICLES.size();
    PARTICLES.resize(PARTICLES.size() + nb_particles);
    for (unsigned long int i = 0; i < nb_particles; i++) {
        double a = ox;
        double b = oy;
        if (randomize) {
            a += (double)std::rand() / RAND_MAX * DX / DENSITY_RACINE;
            b += (double)std::rand() / RAND_MAX * DY / DENSITY_RACINE;
        }
        PARTICLES[offset + i].pos.x = (a + ((double)(i % (width * DENSITY_RACINE)) / DENSITY_RACINE)) * DX;
        PARTICLES[offset + i].pos.y = (b + ((double)(i / (width * DENSITY_RACINE)) / DENSITY_RACINE)) * DY;
        //PARTICLES[i].vel = 0;
    }
    return nb_particles;
}

void Physician::advect() {

    for (unsigned long int p = 0; p < PARTICLES.size(); p++) {
        PARTICLES[p].pos += PARTICLES[p].vel * DT;
        if (PARTICLES[p].pos.x / DX > GRID_WIDTH - 1 || PARTICLES[p].pos.x < 1
            || PARTICLES[p].pos.y / DX > GRID_HEIGHT - 1 || PARTICLES[p].pos.y < 1)
            PARTICLES.erase(PARTICLES.begin() + p);
    }
}
