#pragma once
#include <vector>

class atom
{
private:
  int type;

public:
  int id;
  double x_coord;
  double y_coord;
  double z_coord;

  atom(int ID, int Type, double x, double y, double z);
  ~atom();

  std::vector<double> getCoords();
  int get_id();
};
