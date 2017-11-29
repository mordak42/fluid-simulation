
#include "polynom.hpp"

using namespace mod1;

static Polynom  pi_lagrange(double xj, struct point points[], int nb_point)
{
    Polynom res((double[]){1}, 1);
    double divisor = 1;

    for (int i = 0; i < nb_point; i++)
    {
        if (points[i].x != xj)
        {
            Polynom tmp((double []){-points[i].x, 1.0}, 2);
            res = res * tmp;
            printf("/ %f - %f\n", xj, points[i].x);
            divisor *= (xj - points[i].x);
        }
    }
    res = res / divisor;
    return (res);
}

Polynom lagrange(struct point points[], int nb_point)
{
    Polynom res((double[]){0}, 1);

    for (int j = 0; j < nb_point; j++)
    {
        Polynom tmp = pi_lagrange(points[j].x, points, nb_point);
        tmp = tmp * points[j].y;
        res = res + tmp;
    }
    return res;
}
