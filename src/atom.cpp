#pragma once

#include "../include/atom.h"

atom::atom(int ID, int Type, double x, double y, double z) : id(ID), type(Type), x_coord(x), y_coord(y), z_coord(z)
{
}

std::vector<double> atom::getCoords()
{
  std::vector<double> atomCoord{x_coord, y_coord, z_coord};

  return atomCoord;
}

int atom::get_id() { return id; }
int atom::get_type() { return type; }

atom::~atom()
{
}
