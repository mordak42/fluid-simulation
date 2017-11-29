
#include "polynom.hpp"
#include <iostream>

using namespace mod1;

Polynom::Polynom(double *coefs, int nb_coefs)
{
    if (nb_coefs > NB_COEFS_MAX)                                                // TODO Avoid crash exception
        printf("nb coefs > NB_COEFS_MAX\n");
    memcpy(m_coefs, coefs, nb_coefs * sizeof(double));
    m_nb_coefs = nb_coefs;
}

Polynom::Polynom() {}

Polynom::~Polynom() {}

double Polynom::eval(double x)
{
    double  res = 0;

    for (int i = (m_nb_coefs - 1); i >= 0; i--)
        res = res * x + m_coefs[i];
    return res;
}
