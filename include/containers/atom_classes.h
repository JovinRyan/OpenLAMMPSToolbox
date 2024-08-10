#pragma once

#include <vector>
#include <cmath>
#include <ostream>

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

  void virtual write(std::ostream &stream) const noexcept;

  void virtual write_compute_types(std::ostream &stream) const noexcept;
};

class atom_pe_ke : public atom
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

class atom_varying : public atom
{
private:
public:
  std::vector<double> atom_compute;

  atom_varying(int ID, int Type, double x, double y, double z, std::vector<double> C_vec);

  void write(std::ostream &stream) const noexcept override;
  void write_compute_types(std::ostream &stream) const noexcept override;
};
