#pragma once

#include <vector>

class atom
{
private:
public:
  int id;
  int type;
  double x_coord;
  double y_coord;
  double z_coord;

  atom(int ID, int Type, double x, double y, double z);

  std::vector<double> get_coords();
  int get_id() const;
  int get_type() const;
  double get_displacement(atom ref_atom);
};
