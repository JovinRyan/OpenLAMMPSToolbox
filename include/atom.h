#pragma once
#include <vector>

class atom
{
private:
  int id;
  int type;

public:
  atom(int ID, int Type, double x, double y, double z);
  ~atom();

  std::vector<double> getCoords();

  double x_coord;
  double y_coord;
  double z_coord;
};
