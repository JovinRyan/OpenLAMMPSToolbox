#include "containers/atom_classes.h"

atom::atom(int ID, int Type, double x, double y, double z) : id(ID), type(Type), x_coord(x), y_coord(y), z_coord(z)
{
}

atom::atom(const atom &original_atom) : id(original_atom.get_id()), type(original_atom.get_type()), x_coord(original_atom.get_coords()[0]), y_coord(original_atom.get_coords()[1]), z_coord(original_atom.get_coords()[2])
{
}

std::vector<double> atom::get_coords() const
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

std::vector<double> atom::get_compute_vec() const
{
  throw std::runtime_error("get_compute_vec is not implemented for base class atom");
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

atom_varying::atom_varying(const atom_varying &original_atom) : atom(original_atom), atom_compute(original_atom.get_compute_vec())
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

std::vector<double> atom_varying::get_compute_vec() const noexcept
{
  return atom_compute;
}
