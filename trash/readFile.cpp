#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(std::string filename)
{
	std::ifstream file;
	file.open(filename);
	std::stringstream strstream;
	strstream << file.rdbuf();
	return strstream.str();
}

int main()
{
	std::string toto = readFile("toto.txt");
	std::cout << toto << std::endl;
}

struct velocity_field grid_v[GRID_WIDTH][GRID_HEIGHT + 1];
1D to 2D

for (int i = 0; i < GRID_WIDTH * (GRID_HEIGHT + 1); i++)
{
	grid_v[i / (GRID_HEIGHT + 1)][i % (GRID_HEIGHT + 1)] = toto[i];
}
