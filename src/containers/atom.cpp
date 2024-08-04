#pragma once

#include "../include/atom.h"
#include <cmath>

atom::atom(int ID, int Type, double x, double y, double z) : id(ID), type(Type), x_coord(x), y_coord(y), z_coord(z)
{
}

std::vector<double> atom::get_coords()
{
  return {x_coord, y_coord, z_coord};
}

int atom::get_id() const { return id; }
int atom::get_type() const { return type; }

double atom::get_distance(const atom &ref_atom)
{
  return sqrt((x_coord - ref_atom.x_coord) * (x_coord - ref_atom.x_coord) +
              (y_coord - ref_atom.y_coord) * (y_coord - ref_atom.y_coord) +
              (z_coord - ref_atom.z_coord) * (z_coord - ref_atom.z_coord));
}
