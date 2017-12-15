
#include "pressurer.hpp"
#include <math.h>
using namespace mod1;

Pressurer::Pressurer() {}

Pressurer::~Pressurer() {}

void Pressurer::bzeroVect(double (&vect)[GRID_WIDTH][GRID_HEIGHT]) {
    for (int i = 0 ; i < GRID_WIDTH; i++) {
        for (int j = 0 ; j < GRID_HEIGHT; j++) {
            vect[i][j] = 0;
        }
    }
}

/* return the norm max(abs(vect[i][j])) */
double Pressurer::normeVect(double (&vect)[GRID_WIDTH][GRID_HEIGHT]) {
    double normeMax = 0;
    for (int i = 0 ; i < GRID_WIDTH; i++) {
        for (int j = 0 ; j < GRID_HEIGHT; j++) {
            normeMax = fmax(fabs(vect[i][j]), normeMax);
        }
    }
    return normeMax;
}

/* Perform res = coef * vect
 * not utilized for the moment */
void Pressurer::multScalVect(double coef, double (&vect)[GRID_WIDTH][GRID_HEIGHT], double (&res)[GRID_WIDTH][GRID_HEIGHT]) {
    for (int i = 0 ; i < GRID_WIDTH; i++) {
        for (int j = 0 ; j < GRID_HEIGHT; j++) {
            res[i][j] = coef * vect[i][j];
        }
    }
}

double Pressurer::dotProduct(double (&a)[GRID_WIDTH][GRID_HEIGHT], double (&b)[GRID_WIDTH][GRID_HEIGHT]) {
    double res = 0;
    for (int i = 0 ; i < GRID_WIDTH; i++) {
        for (int j = 0 ; j < GRID_HEIGHT; j++) {
            res += a[i][j] * b[i][j];
        }
    }
    return res;
}

void Pressurer::cpyVect(double (&original)[GRID_WIDTH][GRID_HEIGHT], double (&res)[GRID_WIDTH][GRID_HEIGHT]) {
    for (int i = 0 ; i < GRID_WIDTH; i++) {
        for (int j = 0 ; j < GRID_HEIGHT; j++) {
            res[i][j] = original[i][j];
        }
    }
}

/* Perform res = a + b
 * not utilized for the moment */
void Pressurer::addVect(double (&a)[GRID_WIDTH][GRID_HEIGHT], double (&b)[GRID_WIDTH][GRID_HEIGHT], double (&res)[GRID_WIDTH][GRID_HEIGHT]) {
    for (int i = 0 ; i < GRID_WIDTH; i++) {
        for (int j = 0 ; j < GRID_HEIGHT; j++) {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
}
/* Last step: One time we know pressure, we can update velocity for each cell of grid. */
void Pressurer::updateVelocity(void) {
    double scale = DT / DX;

    for (int i = 0 ; i < GRID_WIDTH; i++) {
        for (int j = 0 ; j < GRID_HEIGHT; j++) {
            if (i > 0 && (GRID_U[i][j].weight > 0 || GRID_U[i - 1][j].weight > 0))
            {
                if (GRID[i][j].type == SOLID || GRID[i - 1][j].type == SOLID)
                    GRID_U[i][j].val = 0;
                else
                    GRID_U[i][j].val -= scale * (p[i][j] - p[i - 1][j]);
            }
            if (j > 0 && (GRID_V[i][j].weight > 0 || GRID_V[i][j - 1].weight > 0))
            {
                if (GRID[i][j].type == SOLID || GRID[i][j - 1].type == SOLID)
                    GRID_V[i][j].val = 0;
                else
                    GRID_V[i][j].val -= scale * (p[i][j] - p[i][j - 1]);
            }
        }
    }
}

/* Initialise A, A etant la matrice du systeme lineaire. */
void Pressurer::calcA()
{
    double scale = DT / (DX * DX); // DENSITY = 1 ?
    for (int i = 0 ; i < GRID_WIDTH; i++) {
        for (int j = 0 ; j < GRID_HEIGHT; j++) {
            A[i][j].diag = 0;
            A[i][j].plusi = 0;
            A[i][j].plusj = 0;
            if (GRID[i][j].type == FLUID) {
                if (i > 0 && GRID[i - 1][j].type == FLUID) {
                    A[i][j].diag += scale;
                }
                if (i < GRID_WIDTH && GRID[i + 1][j].type == FLUID) {
                    A[i][j].diag += scale;
                    A[i][j].plusi -= scale;
                }
                else if (i < GRID_WIDTH && GRID[i + 1][j].type == AIR) {
                    A[i][j].diag += scale;
                }
                if (j > 0 && GRID[i][j - 1].type == FLUID) {
                    A[i][j].diag += scale;
                }
                if (j < GRID_HEIGHT && GRID[i][j + 1].type == FLUID) {
                    A[i][j].diag += scale;
                    A[i][j].plusj -= scale;
                }
                else if (j < GRID_HEIGHT && GRID[i][j + 1].type == AIR) {
                    A[i][j].diag += scale;
                }
            }
        }
    }
}

void::Pressurer::calcPrecon()
{
    double e;
    double tau = 0.97;
    double sigma = 0.25;

    precon[0][0] = 0;
    precon[1][0] = 0;
    precon[0][1] = 0;
    for (int i = 1; i < GRID_WIDTH; i++) {
        for (int j = 1; j < GRID_HEIGHT; j++) {
            precon[i][j] = 0;
            if (GRID[i][j].type == FLUID) {
                e = A[i][j].diag - (A[i - 1][j].plusi * precon[i-1][j] * A[i-1][j].plusi * precon[i-1][j]) -
                    (A[i][j-1].plusj * precon[i][j-1] * A[i][j-1].plusj * precon[i][j-1]) -
                    tau * (A[i-1][j].plusi * A[i-1][j].plusj + 
                            A[i][j-1].plusj *
                            A[i][j-1].plusi);
                if (e < sigma * A[i][j].diag)
                    e = A[i][j].diag;
                precon[i][j] = 1 / sqrt(e);
            }
        }
    }
}

void Pressurer::applyPrecon(double (&r)[GRID_WIDTH][GRID_HEIGHT], double (&res)[GRID_WIDTH][GRID_HEIGHT])
{
    double t;

    q[0][0] = 0;
    q[0][1] = 0;
    q[1][0] = 0;
    for (int i = 1; i < GRID_WIDTH; i++) {
        for (int j = 1; j < GRID_HEIGHT; j++) {
            q[i][j] = 0;
            if (GRID[i][j].type == FLUID) {
                t = r[i][j] - A[i-1][j].plusi * precon[i-1][j] * q[i-1][j]
                    - A[i][j-1].plusj * precon[i][j-1] * q[i][j-1];
                q[i][j] = t * precon[i][j];
            }
        }
    }
    res[GRID_WIDTH - 1][GRID_HEIGHT - 1] = 0;
    res[GRID_WIDTH - 1][GRID_HEIGHT - 2] = 0;
    res[GRID_WIDTH - 2][GRID_HEIGHT - 1] = 0;
    for (int i = GRID_WIDTH - 2; i >= 0; i--) {
        for (int j = GRID_HEIGHT - 2; j >= 0; j--) {
            if (GRID[i][j].type == FLUID) {
                t = q[i][j] - A[i][j].plusi * precon[i][j] * res[i+1][j]
                    - A[i][j].plusj * precon[i][j] * res[i][j+1];
                res[i][j] = t * precon[i][j];
            }
        }
    }
}

/* perform A * s */

void Pressurer::applyA(double (&s)[GRID_WIDTH][GRID_HEIGHT], double (&res)[GRID_WIDTH][GRID_HEIGHT])
{
    double t;
    bzeroVect(res);
    for (int i = 1 ; i < GRID_WIDTH - 1; i++) { // TODO: ATTENTION les case sur les bords sont a 0
        for (int j = 1 ; j < GRID_HEIGHT - 1; j++) {
            if (GRID[i][j].type == FLUID) {
                t = 0;
                t += A[i][j].diag * s[i][j];
                t += A[i][j].plusi * s[i+1][j]; // TODO: depasse GRID_WIDTH
                t += A[i - 1][j].plusi * s[i-1][j];
                t += A[i][j].plusj * s[i][j+1];
                t += A[i][j - 1].plusj * s[i][j-1];
                res[i][j] = t;
            }
        }
    }
}

/* calc b the right hand side of Ap = b */
void Pressurer::calcNegativeDivergence(void) {
    double scale = 1.0 / DX;

    double uSolid = 0;
    double vSolid = 0;
    for (int i = 0 ; i < GRID_WIDTH; i++) {
        for (int j = 0 ; j < GRID_HEIGHT; j++) {

            if (GRID[i][j].type == FLUID) {
                /* calculate negative divergence of velocity */
                b[i][j] = -(scale * (GRID_U[i + 1][j].val - GRID_U[i][j].val +
                        GRID_V[i][j + 1].val - GRID_V[i][j].val));
                /* handle boundary conditions */
                /* but we don't handle moving solids */
                if (i > 0 && GRID[i - 1][j].type == SOLID) {
                    b[i][j] -= scale * (GRID_U[i][j].val - uSolid);
                }
                if (i < GRID_WIDTH && GRID[i + 1][j].type == SOLID) {
                    b[i][j] += scale * (GRID_U[i + 1][j].val - uSolid);
                }
                if (j > 0 && GRID[i][j - 1].type == SOLID) {
                    b[i][j] -= scale * (GRID_V[i][j].val - vSolid);
                }
                if (j < GRID_HEIGHT && GRID[i][j + 1].type == SOLID) {
                    b[i][j] += scale * (GRID_V[i][j + 1].val - vSolid);
                }
            }
            else
                b[i][j] = 0;
        }
    }
}


/*
 * Setinitialguess p=0 
 * andresidualvector r=b
 * (Ifr=0then return p)
 * Set auxiliary vector z = applyPreconditioner(r), 
 * and search vector s = z
 * σ = dotproduct(z, r)
 * Loop until done (or maximum iterations exceeded):
 * Set auxiliary vector z = applyA(s)
 * α = σ/dotproduct(z, s)
 * Update p←p + αs and r←r−αz 
 * If max |r| ≤ tol then return p
 * Set auxiliary vector z = applyPreconditioner(r) 
 * σnew = dotproduct(z, r)
 * β = σnew/σ
 * Setsearchvector s=z+βs
 * σ=σnew
 * Return p (and report iteration limit exceeded)
 */

void::Pressurer::PCG(void) {
    double  tol = 0.000001 * normeVect(b);
    double	sigma;
    double	sigma_new;
    int		i;
    double	alpha;
    double	beta;

    bzeroVect(p);
    cpyVect(b, r);//r = b;
    //std::cout << normeVect(r) << std::endl;
    if (normeVect(r) == 0)
        return ;
    applyPrecon(r, z);
    cpyVect(z, s);//s = z;
    sigma = dotProduct(z, r);
    for (i = 0; i < 200; i++)
    {
        applyA(s, z);
        alpha = sigma / dotProduct(z, s);

        /* p += alpha * s; */
        /* r -= alpha * z; */
        for (int i = 0 ; i < GRID_WIDTH; i++) {
            for (int j = 0 ; j < GRID_HEIGHT; j++) {
                p[i][j] += alpha * s[i][j];
                r[i][j] -= alpha * z[i][j];
            }
        }

        if (normeVect(r) <= tol)
            return ;
        applyPrecon(r, z);

        sigma_new = dotProduct(z, r);
        beta = sigma_new / sigma;

        /* s = z + beta * s */
        for (int i = 0 ; i < GRID_WIDTH; i++) {
            for (int j = 0 ; j < GRID_HEIGHT; j++) {
                s[i][j] = z[i][j] + beta * s[i][j];
            }
        }
        sigma = sigma_new;
    }
    if (i == 200)
        std::cout << "Warning nb max iteration occur in PCG" << std::endl;
}

void Pressurer::solvePressure(void) {
    calcA();
    calcNegativeDivergence();
    calcPrecon();
    PCG();
    updateVelocity();
}
