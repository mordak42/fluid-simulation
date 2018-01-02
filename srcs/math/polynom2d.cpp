
#include "polynom2d.hpp"
#include <iostream>

using namespace mod1;

Polynom2d::Polynom2d(double coefs[NB_COEFS_MAX_2D][NB_COEFS_MAX_2D], int nb_coefs_y, int nb_coefs_x)
{
    if (std::max(nb_coefs_x, nb_coefs_y) > NB_COEFS_MAX_2D)     // TODO Avoid crash exception
        std::cout << "nb coefficients > NB_COEFS_MAX" << std::endl;
    m_nb_coefs_x = nb_coefs_x;
    m_nb_coefs_y = nb_coefs_y;
    for (int y = 0; y < nb_coefs_y; y ++) {
        for (int x = 0; x < nb_coefs_x; x ++) {
            m_coefs[y][x] = coefs[y][x];
        }
    }
}

Polynom2d::Polynom2d() {}

Polynom2d::~Polynom2d() {}

double Polynom2d::eval(double y, double x)
{
    double  res = 0;
    double  acc_y = 1;

    for (int j = (m_nb_coefs_y - 1); j >= 0; j--) {
        double res_line = 0;
        for (int i = (m_nb_coefs_x - 1); i >= 0; i--) {
            res_line = res_line * x + m_coefs[j][i];
        }
        res_line *= acc_y;
        res += res_line;
        acc_y *= y;
    }
    return res;
}

Polynom2d mult(Polynom &p_x, Polynom &p_y)
{
    Polynom2d res;

    res.m_nb_coefs_x = p_x.m_nb_coefs;
    res.m_nb_coefs_y = p_y.m_nb_coefs;

    for (int y = 0; y < res.m_nb_coefs_y; y++) {
        for (int x = 0; x < res.m_nb_coefs_x; x++) {
            res.m_coefs[y][x] = p_y.m_coefs[y] * p_x.m_coefs[x];
        }
    }
    return res;
}
