#include <iostream>
#include <vector>
#include "polynom.hpp"

using namespace mod1;

Polynom lagrange(struct point points[], int nb_point);

void    debug_poly(Polynom poly)
{
    for (int i = poly.m_nb_coefs - 1; i >= 0; i--)
    {
        std::cout << ' ' << poly.m_coefs[i];
        std::cout << "*X^" << i << " + ";
    }
    std::cout << '\n';
}

int main ()
{

    struct point points[3];

    points[0].x = 1;
    points[0].y = 3;
    points[1].x = -1;
    points[1].y = 2;
    points[2].x = 2;
    points[2].y = -1;

    Polynom poly((double[]){0, 1}, 2); // x
    Polynom poly_2((double[]){0, 1}, 2); // x + 1

    //Polynom poly_3 = poly * poly_2;
    Polynom poly_3 = lagrange(points, 3);
    debug_poly(poly_3);


    //std::cout<< "six 1 is equal to" << six->eval(1);
    return 0;
}
