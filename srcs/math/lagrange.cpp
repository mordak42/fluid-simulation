
#include "polynom.hpp"

using namespace mod1;

static Polynom  pi_lagrange(double xj, struct point points[], int nb_point)
{
    Polynom res;
    res.push(1.);
    double divisor = 1;

    for (int i = 0; i < nb_point; i++)
    {
        if (points[i].x != xj)
        {
            Polynom tmp;
            tmp.push(-points[i].x);
            tmp.push(1.);
            res = res * tmp;
            std::cout << "/ " << xj << " - " << points[i].x << std::endl;
            divisor *= (xj - points[i].x);
        }
    }
    res = res / divisor;
    return (res);
}

Polynom lagrange(struct point points[], int nb_point)
{
    Polynom res;
    res.push(0.);

    for (int j = 0; j < nb_point; j++)
    {
        Polynom tmp = pi_lagrange(points[j].x, points, nb_point);
        tmp = tmp * points[j].y;
        res = res + tmp;
    }
    return res;
}
