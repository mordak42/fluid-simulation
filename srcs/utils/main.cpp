#include <iostream>
#include <vector>
#include "polynom.hpp"

using namespace mod1;

int main ()
{
	Polynom poly((double[]){16,2,77,29, 12,23}, 6);
	Polynom poly_2((double[]){16,2,77,29, 12,23}, 6);

	Polynom poly_3 = poly + poly_2;
	for (int i = 0; i < poly_3.m_nb_coefs; i++)
		std::cout << ' ' << poly_3.m_coefs[i];
	std::cout << '\n';
	

//	std::cout<< "six 1 is equal to" << six->eval(1);
	return 0;
}
