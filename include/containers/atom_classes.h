#pragma once

#include <vector>
#include <cmath>

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
  double get_distance(const atom &ref_atom);
};

class atom_pe_ke : atom
{
private:
public:
  double pe;
  double ke;
  atom_pe_ke(int ID, int Type, double x, double y, double z, double PE, double KE);
  double get_total_energy();

  double get_pe() const;
  double get_ke() const;
};
