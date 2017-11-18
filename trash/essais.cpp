#include <iostream>
#include <array>
#include "mod1.hpp"

namespace toto {

void baba() {
	std::cout << "baba" << std::endl;
}

class banane : public std::string 
{
public:
	void printf(std::string str) {
		std::cout << str.c_str() << i << std::endl;
	};

private:
	int i = 3;
};

class string : public std::string
{
	public:
		    void printf(std::string str) {
				        std::cout << str.c_str() << i << std::endl;
						    };

	private:
			    int i = 3;
};


}

namespace tata {

void baba() {
	    std::cout << "bobo" << std::endl;
}
}



using namespace std;

int main(void)
{
	cout << "Hello World" << endl;

	tata::baba();
    toto::baba();

using namespace toto;

	baba();

	toto::banane a;
	std::string str;
	a.printf(str);
	banane b;
	str.append("les sangliers sont laches");
	b.printf(str);

	banane c;
	c.append("voici ma class banane");
	c.printf(c.c_str());

	toto::string d;
	d.append("voici ma class banane");
	d.printf(d.c_str());

//	std::array<int, 4> koko;

	std::array<banane, 4> array;

	array[0].append("voici ma class banane");
    array[0].printf(array[0].c_str());

	

	return 0;
}
