
//#include "polynom.hpp"

#include <iostream>
#include <vector>

namespace mod1
{
class Polynom {
	public:
		Polynom(double *coefs, int size);
		Polynom();
		~Polynom();
		double eval(double x);
		Polynom operator+(Polynom b);
	private:
		/*
		** les coeficiant sont stockes dans l ordre 
		** P(X) = coefs[0] + coefs[1]X + coef[2]X^2 ...
		*/
};
}

using namespace mod1;

Polynom::Polynom(double *coefs, int nb_coefs)
{
	if (nb_coefs > NB_COEFS_MAX)
		printf("nb coefs > NB_COEFS_MAX\n");
	memcpy(m_coefs, coefs, size * sizeof(double));
	degre = nb_coefs - 1;
}

Polynom::Polynom() {
	bzero(m_coefs, NB_COEFS_MAX * sizeof(double));
}

Polynom::~Polynom() {
}

Polynom operator+(Polynom b)
{
	Polynom	res;

	
	return b;
}

double Polynom::eval(double x)
{
	double	res = 0;

	while (42)
	{
		 res = res * x + 1;
	}
	return res;
} 
struct point {
	double x;
	double y;
};

static Polynom	pi_lagrange(double xj, struct point points[], int nb_point)
{
	Polynom	res;
	for (int i = 0; i < nb_point; i++)
	{
		if (points[i].x != xj)
		{
			Polynom tmp((double []){-points[i].x, 1.0}, 2);
			res = res * tmp;
			res = res / (xj - points[i].x);
		}
	}
	return (res);
}

Polynom	Lagrange(struct point points[], int nb_point)
{
	Polynom	res;

	for (int j = 0; j < nb_point; j++)
	{
		res = points[j].y * pi_lagrange(points[j].x, points, nb_point);
	}
	return res;
} 
