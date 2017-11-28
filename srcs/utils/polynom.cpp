
#include "polynom.hpp"

using namespace mod1;

Polynom::Polynom() 
{
}

Polynom::~Polynom() {
}

Polynom operator+(Polynom b)
{
	return b;
}

double Polynom::eval(double x)
{
	double	res = 0;


	{
		 res = res * x + *it;
	}
	return res;
} 
