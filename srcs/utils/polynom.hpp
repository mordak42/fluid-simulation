
#ifndef __POLYNOM_HPP__
# define __POLYNOM_HPP__

#include <iostream>
#define NB_COEFS_MAX 100

namespace mod1
{
class Polynom {
	public:
		Polynom(double *coefs, int size);
		~Polynom();
		double	eval(double x);
		double	m_coefs[NB_COEFS_MAX];
		int		m_nb_coefs;
		/*
		** les coeficiant sont stockes dans l ordre 
		** P(X) = coefs[0] + coefs[1]X + coef[2]X^2 ...
		*/

friend Polynom operator+ (Polynom &p, Polynom &q)
{
	Polynom	res((double[]){0}, 1);
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

};

Polynom	operator + (Polynom &p, Polynom &q);
}


#endif
