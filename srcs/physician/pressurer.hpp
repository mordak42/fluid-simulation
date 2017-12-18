
#ifndef __PRESSURER_HPP__
# define __PRESSURER_HPP__

#include <iostream>
#include <memory>

#include "physicItems.hpp"
#include "physicLaw.hpp"

namespace mod1
{
class Pressurer : public virtual PhysicLaw, public virtual PhysicItems
{
public:
    Pressurer();
    ~Pressurer();
    void solvePressure(void);
private:
    struct Acell {
        float diag;
        float plusi;
        float plusj;
    };

    void updateVelocity(void);
    void calcNegativeDivergence(void);
    void calcA();
    void applyPrecon(float (&r)[GRID_WIDTH][GRID_HEIGHT], float (&res)[GRID_WIDTH][GRID_HEIGHT]);
    void calcPrecon();
    void PCG(void);
    void cpyVect(float (&original)[GRID_WIDTH][GRID_HEIGHT], float (&res)[GRID_WIDTH][GRID_HEIGHT]);
    void applyA(float (&s)[GRID_WIDTH][GRID_HEIGHT], float (&res)[GRID_WIDTH][GRID_HEIGHT]);

    /* utilitaire de vect */
    void addVect(float (&a)[GRID_WIDTH][GRID_HEIGHT], float (&b)[GRID_WIDTH][GRID_HEIGHT], float (&res)[GRID_WIDTH][GRID_HEIGHT]);
    void multScalVect(float coef, float (&vect)[GRID_WIDTH][GRID_HEIGHT], float (&res)[GRID_WIDTH][GRID_HEIGHT]);
    float dotProduct(float (&a)[GRID_WIDTH][GRID_HEIGHT], float (&b)[GRID_WIDTH][GRID_HEIGHT]);
    float normeVect(float (&vect)[GRID_WIDTH][GRID_HEIGHT]);
    void bzeroVect(float (&vect)[GRID_WIDTH][GRID_HEIGHT]);

    struct Acell   A[GRID_WIDTH][GRID_HEIGHT];
    float         precon[GRID_WIDTH][GRID_HEIGHT];
    float         z[GRID_WIDTH][GRID_HEIGHT];
    float         s[GRID_WIDTH][GRID_HEIGHT];
    float         b[GRID_WIDTH][GRID_HEIGHT];
    float         p[GRID_WIDTH][GRID_HEIGHT];
    float         r[GRID_WIDTH][GRID_HEIGHT];

    /* for the applyPrecon */
    float         q[GRID_WIDTH][GRID_HEIGHT];
};
}

#endif
