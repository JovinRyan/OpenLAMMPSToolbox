#include "../include/atom.h"

atom::atom(int ID, int Type, double x, double y, double z) : id(ID), type(Type), x_coord(x), y_coord(y), z_coord(z)
{
}

std::vector<double> atom::get_coords()
{
  std::vector<double> atom_coord{x_coord, y_coord, z_coord};

  return atom_coord;
}

int atom::get_id() { return id; }
int atom::get_type() { return type; }
