
#ifndef __POLYNOM_HPP__
# define __POLYNOM_HPP__

#include <iostream>
#include <string.h>
#include "polynom.hpp"

#define NB_COEFS_MAX_2D 10

namespace mod1
{
class Polynom2d {
    public:
        Polynom2d(double coefs[NB_COEFS_MAX_2D][NB_COEFS_MAX_2D], int nb_coefs_y, int nb_coefs_x);
        Polynom2d();
        ~Polynom2d();
        double eval(double y, double x);
        double  m_coefs[NB_COEFS_MAX_2D][NB_COEFS_MAX_2D] = {{0}};
        int     m_nb_coefs_x = 0;
        int     m_nb_coefs_y = 0;
        /*
         ** Coefficients are stocked on order
         ** P(X) = coefs[0][0] + coefs[1][0]Y + coefs[0][1]X + coef[1][1]XY...
         **  /------- X
         **  |
         **  |
         **  |
         **  Y
         */

        friend Polynom2d operator+ (Polynom2d &p, Polynom2d &q)
        {
            Polynom2d res;

            res.m_nb_coefs_x = std::max(p.m_nb_coefs_x, q.m_nb_coefs_x);
            res.m_nb_coefs_y = std::max(p.m_nb_coefs_y, q.m_nb_coefs_y);
            for (int y = 0; y < res.m_nb_coefs_y; y++) {
                for (int x = 0; x < res.m_nb_coefs_x; x++) {
                    res.m_coefs[y][x] = 0;
                    if (y < p.m_nb_coefs_y && x < p.m_nb_coefs_x)
                        res.m_coefs[y][x] += p.m_coefs[y][x];
                    if (y < q.m_nb_coefs_y && x < q.m_nb_coefs_x)
                        res.m_coefs[y][x] += q.m_coefs[y][x];
                }
            }
            return res;
        }

        friend Polynom2d operator/ (Polynom2d &p, double divisor)
        {
            Polynom2d res(p.m_coefs, p.m_nb_coefs_y, p.m_nb_coefs_x);

            for (int y = 0; y < res.m_nb_coefs_y; y++) {
                for (int x = 0; x < res.m_nb_coefs_x; x++) {
                    res.m_coefs[y][x] = p.m_coefs[y][x] / divisor;
                }
            }
            return res;
        }

        friend Polynom2d operator* (Polynom2d &p, double factor)
        {
            Polynom2d res(p.m_coefs, p.m_nb_coefs_y, p.m_nb_coefs_x);

            for (int y = 0; y < res.m_nb_coefs_y; y++) {
                for (int x = 0; x < res.m_nb_coefs_x; x++) {
                    res.m_coefs[y][x] = p.m_coefs[y][x] * factor;
                }
            }
            return res;
        }

        /*
         ** P_x est un polynome de la variable x et p_y de la variable y
         ** uniquement
         */

};
}

mod1::Polynom2d lagrange2d(struct mod1::point points[], int nb_point);

#endif

