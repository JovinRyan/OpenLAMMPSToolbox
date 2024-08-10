#include "containers/atom_classes.h"

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

void atom::write(std::ostream &stream) const noexcept
{
  stream << id << " " << type << " " << x_coord << " " << y_coord << " " << z_coord;
}

void atom::write_compute_types(std::ostream &stream) const noexcept
{
}

atom_pe_ke::atom_pe_ke(int ID, int Type, double x, double y, double z, double PE, double KE) : atom(ID, Type, x, y, z), pe(PE), ke(KE)
{
}

double atom_pe_ke::get_pe() const { return pe; }
double atom_pe_ke::get_ke() const { return ke; }

double atom_pe_ke::get_total_energy()
{
  return pe + ke;
}

atom_varying::atom_varying(int ID, int Type, double x, double y, double z, std::vector<double> C_vec) : atom(ID, Type, x, y, z), atom_compute(std::move(C_vec))
{
}

void atom_varying::write(std::ostream &stream) const noexcept
{
  atom::write(stream);
  for (const auto &value : atom_compute)
  {
    stream << " " << value << " ";
  }
}

void atom_varying::write_compute_types(std::ostream &stream) const noexcept
{
  for (int i = 0; i < size(atom_compute); i++)
  {
    stream << " " << "var_" << i + 1;
  }
}
