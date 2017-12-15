#include <fstream>
#include <iostream>
#include <vector>

#define LEVELSET(k, j, i) levelSet[k * dimy * dimx + j * dimx + i]

int main () {
  int dimx, dimy, dimz;
  double dx, ox, oy, oz;
  std::fstream fs;
  fs.open ("budda.sdf", std::fstream::in);

  fs >> dimx;
  fs >> dimy;
  fs >> dimz;
  fs >> ox;
  fs >> oy;
  fs >> oz;
  fs >> dx;
  std::cout << dimx << std::endl;
  std::cout << dimy << std::endl;
  std::cout << dimz << std::endl;
  std::cout << ox << std::endl;
  std::cout << oy << std::endl;
  std::cout << oz << std::endl;
  std::cout << dx << std::endl;

  std::vector<double> levelSet(dimx * dimy * dimz);
  for (int i = 0; i < dimx * dimy * dimz; i++)
  {
      double val;
      fs >> val;
      levelSet[i] = val;
     // std::cout << val << std::endl;
     // std::cout << levelSet[i] << std::endl;
  }
  std::cout << LEVELSET(45, 104, 45);
  fs.close();

  return 0;
}
