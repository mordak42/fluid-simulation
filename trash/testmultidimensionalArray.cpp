#include "chronometric.hpp"
#include <fstream>
#include <iostream>
#include <vector>

#define GRIDONEDIM(i, j, k) lolo->gridOneDim[k * 10000  + j * 100 + i]
using namespace lib;

struct cell
{
    double x;
};

struct lala
{
     struct cell gridMultiDim[100][100][100];
     struct cell gridOneDim[100 * 100 *100];
};

int main () {
    int dim = 100;

    Chronometric chrono;
    struct lala *lolo = new struct lala;
/*
    std::vector<struct cell> vect;
    vect.resize(100 * 100 * 100);
    chrono.reset();
    for (int i = 1; i < dim - 1; i++)
        for (int j = 1; j < dim - 1; j++)
            for (int k = 1; k < dim - 1; k++)
                vect[k * 10000  + j * 100 + i].x = 42;
    std::cout << chrono.getTime() << std::endl;
*/
    chrono.reset();
    for (int i = 1; i < dim - 1; i++)
        for (int j = 1; j < dim - 1; j++)
            for (int k = 1; k < dim - 1; k++)
                lolo->gridMultiDim[i][j][k].x = 42;
    std::cout << chrono.getTime() << std::endl;
    /*
    chrono.reset();
    for (int i = 1; i < dim - 1; i++)
        for (int j = 1; j < dim - 1; j++)
            for (int k = 1; k < dim - 1; k++)
                lolo->gridOneDim[k * 10000  + j * 100 + i].x = 42;
    std::cout << chrono.getTime() << std::endl;
    */

/*
    for (int i = 1; i < dim - 1; i++)
        for (int j = 1; j < dim - 1; j++)
            for (int k = 1; k < dim - 1; k++) {
                std::cout << GRIDONEDIM(i, j, k).x << std::endl;
                std::cout << lolo->gridMultiDim[i][j][k].x << std::endl;
            }
*/
    return 0;
}

