
#include <random>
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

void Physician::updateGridLabel() {
    for (unsigned long int p = 0; p < PARTICLES.size(); p++) {
        int gi = PARTICLES[p].pos.x / DX;
        int gj = PARTICLES[p].pos.y / DY;
        if (GRID[gi][gj].type == AIR)
            GRID[gi][gj].type = FLUID;
    }
}

void Physician::saveVelocity() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            GRID_U[i][j].oldVal = GRID_U[i][j].val;
            GRID_V[i][j].oldVal = GRID_V[i][j].val;
        }
    }
}

double Physician::moyU(int i, int j)
{
	double sum = 0;
	double weight = 0;

	if (GRID[i - 1][j].type == FLUID) {
		sum += GRID_U[i - 1][j].val;
		weight += 1;
	}
	if (GRID[i + 1][j].type == FLUID) {
		sum += GRID_U[i + 1][j].val;
		weight += 1;
	}
	if (GRID[i][j + 1].type == FLUID) {
		sum += GRID_U[i][j + 1].val;
		weight += 1;
	}
	if (GRID[i][j - 1].type == FLUID) {
		sum += GRID_U[i][j - 1].val;
		weight += 1;
	}
	return (sum / weight);
}

double Physician::moyV(int i, int j)
{
	double sum = 0;
	double weight = 0;

	if (GRID_V[i - 1][j].val != 0) {
		sum += GRID_V[i - 1][j].val;
		weight += 1;
	}
	if (GRID_V[i + 1][j].val != 0) {
		sum += GRID_V[i + 1][j].val;
		weight += 1;
	}
	if (GRID_V[i][j + 1].val != 0) {
		sum += GRID_V[i][j + 1].val;
		weight += 1;
	}
	if (GRID_V[i][j - 1].val != 0) {
		sum += GRID_V[i][j - 1].val;
		weight += 1;
	}
	if (weight != 0)
		return (sum / weight);
	return 0;
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
				if (GRID_V[i][j].val == 0)
				{
					GRID_V[i][j].val = moyV(i, j);
                    GRID_V[i][j].weight = 1;
					//std::cout << "moy v: " << GRID_V[i][j].val;
				}
				if (GRID_V[i][j + 1].val == 0) {
					GRID_V[i][j + 1].val = moyV(i, j + 1);
                    GRID_V[i][j + 1].weight = 1;
                }
                GRID[i][j].type = SURROUND;
			}
		}
	}
	for (int i = 1; i < GRID_WIDTH - 1; i++)
		for (int j = 1; j < GRID_HEIGHT - 1; j++)
            if (GRID[i][j].type == SURROUND) {
                GRID[i][j].type = FLUID;
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
		offset = vector3d(0.0, hdx, 0);
	else
		offset = vector3d(hdx, 0.0, 0);
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
			GRID_U[i][j].oldVal = 0;
			GRID_V[i][j].oldVal = 0;
			GRID_V[i][j].val = 0;
			GRID_U[i][j].val = 0;
			if (GRID[i][j].type == FLUID)
				GRID[i][j].type = AIR;
		}
	}

	for (unsigned long int p = 0; p < PARTICLES.size(); p++) {
		//std::cout << "x"<<x <<"y" << y << "velx"<< up << "vely" << vp <<std::endl;

		int i = PARTICLES[p].pos.x / DX;
		int j = PARTICLES[p].pos.y / DY;
		if (i < 0 || i >= GRID_WIDTH)
			continue;
		if (j < 0 || j >= GRID_HEIGHT)
			continue;
		/*  if (GRID[i - 1][j].type == AIR)
			GRID[i - 1][j].type = FLUID;
			if (GRID[i + 1][j].type == AIR)
			GRID[i + 1][j].type = FLUID;
			if (GRID[i][j + 1].type == AIR)
			GRID[i][j + 1].type = FLUID;
			*/
		if (GRID[i][j].type == AIR)
			GRID[i][j].type = FLUID;

		vector3d pos = PARTICLES[p].pos;
		vector3d vel = PARTICLES[p].vel;

		evaluateGridVelocityAtPosition(pos, vel, i, j, 'u');
		evaluateGridVelocityAtPosition(pos, vel, i + 1, j, 'u');
		evaluateGridVelocityAtPosition(pos, vel, i, j, 'v');
		evaluateGridVelocityAtPosition(pos, vel, i, j + 1, 'v');
	}

	for (int i = 0; i < GRID_WIDTH + 1; i++) {
		for (int j = 0; j < GRID_HEIGHT + 1; j++) {
			if (j < GRID_HEIGHT && GRID_U[i][j].weight) {
				GRID_U[i][j].val = GRID_U[i][j].sum / GRID_U[i][j].weight;
				GRID_U[i][j].oldVal = GRID_U[i][j].val;
			}
			if (i < GRID_WIDTH && GRID_V[i][j].weight) {
				GRID_V[i][j].val = GRID_V[i][j].sum / GRID_V[i][j].weight;
				GRID_V[i][j].oldVal = GRID_V[i][j].val;
			}
		}
	}
}

double Physician::cubicInterpolate(double p[4], double s) {
    /* Bridson interpolation */
     return (-0.3 * s + 0.5 * s * s - 0.16 * s * s * s) * p[0]
       + (1 - s * s + 0.5 * (s * s * s - s)) * p[1]
       + (s + 0.5 * (s * s - s * s * s)) *p[2]
       + (0.16 * (s * s * s - s)) * p[3];

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
    position -= gridOffset;
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
                if (grid_i >= 0 && grid_i < GRID_WIDTH + 1 && grid_j >= 0 && grid_j < GRID_HEIGHT)
                {
                    if (method == 'p') /* PIC */
                        points[j][i] = GRID_U[grid_i][grid_j].val;
                    else              /* FLIP */
                        points[j][i] = GRID_U[grid_i][grid_j].val - GRID_U[grid_i][grid_j].oldVal;
                }
                else
                    points[j][i] = 0;
            }
            else
            {
                if (grid_i >= 0 && grid_i < GRID_WIDTH && grid_j >= 0 && grid_j < GRID_HEIGHT + 1)
                {
                    if (method == 'p') 
                        points[j][i] = GRID_V[grid_i][grid_j].val;
                    else
                        points[j][i] = GRID_V[grid_i][grid_j].val - GRID_V[grid_i][grid_j].oldVal;
                }
                else
                    points[j][i] = 0;
            }
        }
    }
    vector3d gpos = vector3d(gi, gj, 0) * DX;
    vector3d interp = (position - gpos) / DX;
    return bicubicInterpolate(points, interp.x, interp.y);
}

vector3d Physician::evaluateVelocityAtPosition(vector3d position, char method) {
    double hdx = 0.5 * DX;
    vector3d offsetU(0.0, hdx, 0);
    vector3d offsetV(hdx, 0.0, 0);
    /* 3D model -> vector3d offsetW(hdx, hdx, 0.0); */

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

uint32_t Physician::initParticules(uint32_t ox, uint32_t oy, uint32_t width, uint32_t height, bool randomize) {
    if (ox + width >= GRID_WIDTH || oy + height >= GRID_HEIGHT) {
        std::cerr << "Some particles will be outside the grid: " << ox + width << " " << oy + height << " on " << GRID_WIDTH << "*" << GRID_HEIGHT << std::endl;
        return 0;
    }
    uint32_t nb_particles = width * height * DENSITY_RACINE * DENSITY_RACINE;
    if (nb_particles == 0) {
        std::cerr << "There are no particle to fill it" << std::endl;
        return 0;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    size_t offset = PARTICLES.size();
    PARTICLES.resize(PARTICLES.size() + nb_particles);
    for (unsigned long int i = 0; i < nb_particles; i++) {
        double a = ox;
        double b = oy;
        if (randomize) {
            a += dis(gen) * DX / DENSITY_RACINE;
            b += dis(gen) * DY / DENSITY_RACINE;
        }
        PARTICLES[offset + i].pos.x = (a + ((double)(i % (width * DENSITY_RACINE)) / DENSITY_RACINE)) * DX;
        PARTICLES[offset + i].pos.y = (b + ((double)(i / (width * DENSITY_RACINE)) / DENSITY_RACINE)) * DY;
    }
    return nb_particles;
}

void Physician::femmeFontaine(uint32_t ox, uint32_t oy, double vel) {
    size_t nb_particles = 4;
    size_t offset = PARTICLES.size();
    PARTICLES.resize(PARTICLES.size() + nb_particles);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (unsigned long int i = 0; i < nb_particles; i++) {
        double a = ox;
        double b = oy;
        a += dis(gen) * DX / DENSITY_RACINE;
        b += dis(gen) * DY / DENSITY_RACINE;
        PARTICLES[offset + i].pos.x = a * DX;
        PARTICLES[offset + i].pos.y = b * DY;
        PARTICLES[offset + i].vel.x = 0;
        PARTICLES[offset + i].vel.y = vel;
    }
}

void Physician::pluieDiluvienne() {
    std::srand(std::time(0));
    size_t offset = PARTICLES.size();
    PARTICLES.resize(PARTICLES.size() + 1);
    double a = 0;
    double b = GRID_HEIGHT - 4;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    a += dis(gen) * (GRID_WIDTH - 4);
    PARTICLES[offset].pos.x = 0 + a * DX;
    PARTICLES[offset].pos.y = b * DY;
}


/* This advection formula is better in a close space, with huge walls around the screen. */
/*
* void Physician::advect() {
*
*    for (unsigned long int p = 0; p < PARTICLES.size(); p++) {
*        PARTICLES[p].pos += PARTICLES[p].vel * DT;
*        if (PARTICLES[p].pos.x / DX > GRID_WIDTH - 1 || PARTICLES[p].pos.x < 1
*                || PARTICLES[p].pos.y / DX > GRID_HEIGHT - 1 || PARTICLES[p].pos.y < 1)
*            PARTICLES.erase(PARTICLES.begin() + p);
*    }
* }
*/

/* This advection formula is better in a open space, when mass particles left from the screen. */
void Physician::advect() {

    size_t cn = 0;

    for (unsigned long int p = 0; p < PARTICLES.size(); p++) {
        /* set the new positions of particles */
        PARTICLES[p].pos += PARTICLES[p].vel * DT;

        /* for the particles which left the grid, delete it */
        double posX = PARTICLES[p].pos.x / DX;
        double posY = PARTICLES[p].pos.y / DY;

        if (posX <= GRID_WIDTH - 1
                && posX >= 1
                && posY <= GRID_HEIGHT - 1
                && posY >= 1
                /* With this condition, the particles in the SOLID case are just deleted ! */
                && GRID[(int)posX][(int)posY].type != SOLID)

        {
            PARTICLES[cn++] = PARTICLES[p];
        }
    }
    PARTICLES.resize(cn);
}
