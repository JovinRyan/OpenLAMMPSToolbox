#pragma once

#include "atom.h"

class atom_pe_ke : atom
{
private:
public:
  double pe;
  double ke;
  atom_pe_ke(int ID, int Type, double x, double y, double z, double PE, double KE);
};
