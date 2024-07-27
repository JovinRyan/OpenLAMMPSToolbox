#pragma once

#include <vector>
#include "../include/atom.h"

atom::atom(int ID, int Type, double x, double y, double z) : id(ID), type(Type), x_coord(x), y_coord(y), z_coord(z)
{
}

std::vector<double> atom::getCoords()
{
  std::vector<double> atomCoord{x_coord, y_coord, z_coord};

  return atomCoord;
}

atom::~atom()
{
}
