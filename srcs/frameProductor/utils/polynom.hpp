
#ifndef __POLYNOM_HPP__
# define __POLYNOM_HPP__

#include <iostream>
#define NB_COEFS_MAX 100

struct point {
    double x;
    double y;
};

namespace mod1
{
    class Polynom {
        public:
            Polynom(double *coefs, int size);
            ~Polynom();
            double  eval(double x);
            double  m_coefs[NB_COEFS_MAX] = {0};
            int     m_nb_coefs;
            /*
             ** les coeficiant sont stockes dans l ordre 
             ** P(X) = coefs[0] + coefs[1]X + coef[2]X^2 ...
             */

            friend Polynom operator+ (Polynom &p, Polynom &q)
            {
                Polynom res((double[]){0}, 1);
                int i = 0;

                res.m_nb_coefs = p.m_nb_coefs > q.m_nb_coefs ? p.m_nb_coefs : q.m_nb_coefs;
                for (; i < p.m_nb_coefs && i < q.m_nb_coefs; i++)
                    res.m_coefs[i] = p.m_coefs[i] + q.m_coefs[i];
                for (; i < p.m_nb_coefs; i++)
                    res.m_coefs[i] = p.m_coefs[i];
                for (; i < q.m_nb_coefs; i++)
                    res.m_coefs[i] = q.m_coefs[i];
                return res;
            }

            friend Polynom operator/ (Polynom &p, double divisor)
            {
                Polynom res((double*)p.m_coefs, p.m_nb_coefs);

                for (int i = 0; i < p.m_nb_coefs; i++)
                    res.m_coefs[i] = p.m_coefs[i] / divisor;
                return res;
            }

            friend Polynom operator* (Polynom &p, double factor)
            {
                Polynom res((double*)p.m_coefs, p.m_nb_coefs);

                for (int i = 0; i < p.m_nb_coefs; i++)
                    res.m_coefs[i] = p.m_coefs[i] * factor;
                return res;
            }

            /*
             ** P(X) * Q(X)[i] = ∑(k = 0; k <=i) p[k]q[i-k]
             */

            friend Polynom operator* (Polynom &p, Polynom &q)
            {
                Polynom res((double[]){0}, 1);

                res.m_nb_coefs = p.m_nb_coefs + q.m_nb_coefs - 1;

                for (int i = 0; i < res.m_nb_coefs; i++) {
                    res.m_coefs[i] = 0;
                    for (int k = 0; k <= i; k++)
                        res.m_coefs[i] += p.m_coefs[k] * q.m_coefs[i - k];
                }
                return res;
            }
    };

}

#endif
