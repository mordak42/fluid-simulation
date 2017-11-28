#include <iostream>
#include <vector>
#include "polynom.hpp"

using namespace mod1;

int main ()
{
		std::vector<int> first;                                // empty vector of ints
	std::vector<int> second (4,100);                       // four ints with value 100
	std::vector<int> third (second.begin(),second.end());  // iterating through second
	std::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29, 12,23};

	std::vector<int> fifth (myints, myints + 16 / sizeof(int) );
	
	Polynom *six = new Polynom((double[]){16,2,77,29, 12,23});
printf("%lu\n", sizeof(myints));

	new Array(3, 4, 5, 75, 45);

	for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	

//	std::cout<< "six 1 is equal to" << six->eval(1);
	return 0;
}
