#pragma once

#include "../include/atom.h"
#include <cmath>

atom::atom(int ID, int Type, double x, double y, double z) : id(ID), type(Type), x_coord(x), y_coord(y), z_coord(z)
{
}

std::vector<double> atom::get_coords()
{
  std::vector<double> atom_coord{x_coord, y_coord, z_coord};

  return atom_coord;
}

int atom::get_id() const { return id; }
int atom::get_type() const { return type; }

double atom::get_displacement(atom ref_atom)
{
  double displacement = sqrt((x_coord - ref_atom.get_coords()[0]) * (x_coord - ref_atom.get_coords()[0]) +
                             (y_coord - ref_atom.get_coords()[1]) * (y_coord - ref_atom.get_coords()[1]) +
                             (z_coord - ref_atom.get_coords()[2]) * (z_coord - ref_atom.get_coords()[2]));

  return displacement;
}
