
//#include "polynom.hpp"

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
