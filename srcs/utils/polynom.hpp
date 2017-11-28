
#ifndef __POLYNOM_HPP__
# define __POLYNOM_HPP__

#include <iostream>
#include <vector>

namespace mod1
{
class Polynom {
	public:
		Polynom(double init_coefs[]);
		~Polynom();
		double eval(double x);
		Polynom operator+(Polynom b);
	private:
		std::vector<double> m_coefs;
		/*
		** les coeficiant sont stockes dans l ordre 
		** P(X) = coefs[0] + coefs[1]X + coef[2]X^2 ...
		*/
};
}

#endif
