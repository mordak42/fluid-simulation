
#ifndef __PRESSURER_HPP__
# define __PRESSURER_HPP__

#include <iostream>
#include <memory>

#include "physicItems.hpp"
#include "physicLaw.hpp"

struct Acell {
    double diag;
    double plusi;
    double plusj;
};


namespace mod1
{
    class Pressurer : public virtual PhysicLaw
    {
        public:
            Pressurer(const std::shared_ptr<PhysicItems> &physicItems);
            ~Pressurer();
            void solvePressure(void);
        private:
            void updateVelocity(void);
            void calcNegativeDivergence(void);
            void calcA();
            void applyPrecon(double (&r)[GRID_WIDTH][GRID_HEIGHT], double (&res)[GRID_WIDTH][GRID_HEIGHT]);
            void calcPrecon();
            void PCG(void);
            void cpyVect(double (&original)[GRID_WIDTH][GRID_HEIGHT], double (&res)[GRID_WIDTH][GRID_HEIGHT]);
            void applyA(double (&s)[GRID_WIDTH][GRID_HEIGHT], double (&res)[GRID_WIDTH][GRID_HEIGHT]);

            /* utilitaire de vect */
            void addVect(double (&a)[GRID_WIDTH][GRID_HEIGHT], double (&b)[GRID_WIDTH][GRID_HEIGHT], double (&res)[GRID_WIDTH][GRID_HEIGHT]);
            void multScalVect(double coef, double (&vect)[GRID_WIDTH][GRID_HEIGHT], double (&res)[GRID_WIDTH][GRID_HEIGHT]);
            double dotProduct(double (&a)[GRID_WIDTH][GRID_HEIGHT], double (&b)[GRID_WIDTH][GRID_HEIGHT]);
            double normeVect(double (&vect)[GRID_WIDTH][GRID_HEIGHT]);
            void bzeroVect(double (&vect)[GRID_WIDTH][GRID_HEIGHT]);

            const std::shared_ptr<PhysicItems> &m_physicItems;
            struct Acell   A[GRID_WIDTH][GRID_HEIGHT];
            double	       precon[GRID_WIDTH][GRID_HEIGHT];
            double	       z[GRID_WIDTH][GRID_HEIGHT];
            double	       s[GRID_WIDTH][GRID_HEIGHT];
            double	       b[GRID_WIDTH][GRID_HEIGHT];
            double	       p[GRID_WIDTH][GRID_HEIGHT];
            double	       r[GRID_WIDTH][GRID_HEIGHT];

            /* for intermediate calculus */
            double	       tmp[GRID_WIDTH][GRID_HEIGHT];
            /* for the applyPrecon */
            double	       q[GRID_WIDTH][GRID_HEIGHT];
    };
}

#endif
